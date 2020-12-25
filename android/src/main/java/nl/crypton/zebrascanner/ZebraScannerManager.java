package nl.crypton.zebrascanner;

import android.util.Log;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;
import com.facebook.react.modules.core.DeviceEventManagerModule;
import com.zebra.scannercontrol.DCSSDKDefs;
import com.zebra.scannercontrol.DCSScannerInfo;
import com.zebra.scannercontrol.FirmwareUpdateEvent;
import com.zebra.scannercontrol.IDcsSdkApiDelegate;
import com.zebra.scannercontrol.SDKHandler;

import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

class Scanner {
    private int scannerId;
    private String name;

    public Scanner(int scannerId, String name) {
        this.scannerId = scannerId;
        this.name = name;
    }

    public int getScannerId() {
        return scannerId;
    }

    public String getName() {
        return name;
    }
}

public class ZebraScannerManager implements IDcsSdkApiDelegate {
    private SDKHandler sdkHandler;
    private ReactApplicationContext reactContext;
    private List<nl.crypton.zebrascanner.Scanner> activeScanners = new ArrayList<>();
    private static final String TAG = "ZebraScannerManager";

    public ZebraScannerManager(ReactApplicationContext reactContext) {
        this.reactContext = reactContext;
        sdkHandler = new SDKHandler(reactContext);
        sdkHandler.dcssdkSetDelegate(this);

        this.setupApi();
    }

    // Public Functions
    public void setEnabled(boolean isEnabled) {
        for (Scanner item: activeScanners) {
            enableScanner(item.getScannerId(), isEnabled);
        }
    }

    public List<Scanner> getActiveScanners() {
        return activeScanners;
    }

    // Private Functions
    private void setupApi() {
        int notifyMask = 0;
        // We would like to subscribe to all scanner available/not-available events
        notifyMask |=
                DCSSDKDefs.DCSSDK_EVENT.DCSSDK_EVENT_SCANNER_APPEARANCE.value |
                        DCSSDKDefs.DCSSDK_EVENT.DCSSDK_EVENT_SCANNER_DISAPPEARANCE.value;
        // We would like to subscribe to all scanner connection events
        notifyMask |=
                DCSSDKDefs.DCSSDK_EVENT.DCSSDK_EVENT_SESSION_ESTABLISHMENT.value |
                        DCSSDKDefs.DCSSDK_EVENT.DCSSDK_EVENT_SESSION_TERMINATION.value;
        // We would like to subscribe to all barcode events
        notifyMask |= DCSSDKDefs.DCSSDK_EVENT.DCSSDK_EVENT_BARCODE.value;

        try {
            sdkHandler.dcssdkSetOperationalMode(DCSSDKDefs.DCSSDK_MODE.DCSSDK_OPMODE_BT_NORMAL);

            // Enable scanner detection
            sdkHandler.dcssdkEnableAvailableScannersDetection(true);

            sdkHandler.dcssdkSubsribeForEvents(notifyMask);

            // Get list of active scanners
            List<DCSScannerInfo> scanners = sdkHandler.dcssdkGetActiveScannersList();
            for (DCSScannerInfo scanner: scanners) {
                addScanner(scanner.getScannerID(), scanner.getScannerName());
            }

        } catch (Exception e) {
            Log.e(TAG, "Exception in setupApi", e);
        }
    }

    private void sendEvent(String eventName,
                           WritableMap params) {
        try {
            this.reactContext
                    .getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
                    .emit(eventName, params);
        } catch (Exception e) {
            Log.e(TAG, "Exception in sendEvent", e);
        }
    }

    private void sendEvent(String eventName, int scannerId) {
        WritableMap params = new WritableNativeMap();
        params.putInt("id", scannerId);

        sendEvent(eventName, params);
    }

    private void enableScanner(int scannerId, boolean isEnabled) {
        StringBuilder outXML = new StringBuilder();
        DCSSDKDefs.DCSSDK_COMMAND_OPCODE opCode
                = DCSSDKDefs.DCSSDK_COMMAND_OPCODE.DCSSDK_DEVICE_SCAN_DISABLE;
        if (isEnabled) {
            opCode = DCSSDKDefs.DCSSDK_COMMAND_OPCODE.DCSSDK_DEVICE_SCAN_ENABLE;
        }

        String inXml = "<inArgs><scannerID>" + scannerId + "</scannerID></inArgs>";
        sdkHandler.dcssdkExecuteCommandOpCodeInXMLForScanner(opCode, inXml, outXML, scannerId);
    }

    private void addScanner(int scannerId, String name) {
        Scanner scanner = null;
        for (Scanner item: activeScanners) {
            if (item.getScannerId() == scannerId) {
                scanner = item;
                break;
            }
        }

        if (scanner == null) {
            activeScanners.add(new Scanner(scannerId, name));
        }
    }

    private void removeScanner(int scannerId) {
        Scanner scanner = null;
        for (Scanner item: activeScanners) {
            if (item.getScannerId() == scannerId) {
                scanner = item;
                break;
            }
        }
        if (scanner != null) {
            activeScanners.remove(scanner);
        }
    }

    // Scanner SDK Delegate Methods
    @Override
    public void dcssdkEventScannerAppeared(DCSScannerInfo dcsScannerInfo) {
        addScanner(dcsScannerInfo.getScannerID(), dcsScannerInfo.getScannerName());
        sdkHandler.dcssdkEstablishCommunicationSession(dcsScannerInfo.getScannerID());

        sendEvent("scanner-appeared", dcsScannerInfo.getScannerID());
    }

    @Override
    public void dcssdkEventScannerDisappeared(int scannerId) {
        removeScanner(scannerId);
        sendEvent("scanner-disappeared", scannerId);
    }

    @Override
    public void dcssdkEventCommunicationSessionEstablished(DCSScannerInfo dcsScannerInfo) {
        sendEvent("scanner-connected", dcsScannerInfo.getScannerID());
    }

    @Override
    public void dcssdkEventCommunicationSessionTerminated(int scannerId) {
        sendEvent("scanner-disconnected", scannerId);
    }

    @Override
    public void dcssdkEventBarcode(byte[] barcodeData, int type, int scannerId) {
        WritableMap params = new WritableNativeMap();
        params.putInt("id", scannerId);
        params.putString("barcode", new String(barcodeData));
        params.putInt("type", type);

        sendEvent("scanner-barcode", params);
    }

    @Override
    public void dcssdkEventImage(byte[] data, int scannerId) {

    }

    @Override
    public void dcssdkEventVideo(byte[] data, int scannerId) {

    }

    @Override
    public void dcssdkEventBinaryData(byte[] data, int scannerId) {

    }

    @Override
    public void dcssdkEventFirmwareUpdate(FirmwareUpdateEvent firmwareUpdateEvent) {

    }

    @Override
    public void dcssdkEventAuxScannerAppeared(DCSScannerInfo dcsScannerInfo, DCSScannerInfo dcsScannerInfo1) {

    }
}

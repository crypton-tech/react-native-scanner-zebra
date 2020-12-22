package nl.crypton.zebrascanner;

import com.facebook.react.bridge.JavaOnlyMap;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;
import com.facebook.react.modules.core.DeviceEventManagerModule;
import com.zebra.scannercontrol.DCSSDKDefs;
import com.zebra.scannercontrol.DCSScannerInfo;
import com.zebra.scannercontrol.FirmwareUpdateEvent;
import com.zebra.scannercontrol.IDcsSdkApiDelegate;
import com.zebra.scannercontrol.SDKHandler;

public class ZebraScannerManager implements IDcsSdkApiDelegate {
    private SDKHandler sdkHandler;
    private ReactApplicationContext reactContext;

    public ZebraScannerManager(ReactApplicationContext reactContext) {
        this.reactContext = reactContext;
        sdkHandler = new SDKHandler(reactContext);
        sdkHandler.dcssdkSetDelegate(this);

        this.setupApi();
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

        sdkHandler.dcssdkSetOperationalMode(DCSSDKDefs.DCSSDK_MODE.DCSSDK_OPMODE_BT_NORMAL);

        // enable scanner detection
        sdkHandler.dcssdkEnableAvailableScannersDetection(true);

        sdkHandler.dcssdkSubsribeForEvents(notifyMask);
    }

    private void sendEvent(String eventName,
                           WritableMap params) {
        this.reactContext
                .getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
                .emit(eventName, params);
    }

    private void sendEvent(String eventName, int scannerId) {
        WritableMap params = new WritableNativeMap();
        params.putInt("id", scannerId);

        sendEvent("scanner-barcode", params);
    }

    // Scanner SDK Delegate Methods
    @Override
    public void dcssdkEventScannerAppeared(DCSScannerInfo dcsScannerInfo) {
        sendEvent("scanner-appeared", dcsScannerInfo.getScannerID());
    }

    @Override
    public void dcssdkEventScannerDisappeared(int scannerId) {
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

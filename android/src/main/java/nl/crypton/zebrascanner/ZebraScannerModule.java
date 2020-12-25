package nl.crypton.zebrascanner;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeArray;
import com.facebook.react.bridge.WritableNativeMap;

import java.util.List;

public class ZebraScannerModule extends ReactContextBaseJavaModule {

    private final ReactApplicationContext reactContext;
    private final ZebraScannerManager scannerManager;

    public ZebraScannerModule(ReactApplicationContext reactContext) {
        super(reactContext);
        this.reactContext = reactContext;
        this.scannerManager = new ZebraScannerManager(reactContext);
    }

    @Override
    public String getName() {
        return "ZebraScanner";
    }

    @ReactMethod
    public void setEnabled(boolean isEnabled) {
        this.scannerManager.setEnabled(isEnabled);
    }

    @ReactMethod
    public void getActiveScanners(Callback callback) {
        List<Scanner> scanners = scannerManager.getActiveScanners();
        WritableArray writableScanners = new WritableNativeArray();

        for (Scanner item: scanners) {
            WritableMap scannerMap = new WritableNativeMap();
            writableScanners.pushMap(scannerMap);
            scannerMap.putInt("id", item.getScannerId());
            scannerMap.putString("name", item.getName());
        }

        callback.invoke(writableScanners);
    }
}

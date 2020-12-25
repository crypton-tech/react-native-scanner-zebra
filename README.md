# react-native-scanner-zebra

*Note: This package is still under beta version**

## Getting started

`$ npm install react-native-scanner-zebra --save`

### Mostly automatic installation

`$ react-native link react-native-scanner-zebra`

### Additions steps for IOS Application

* Configure the Xcode project to support one or more external accessory communication protocols through the UISupportedExternalAccessoryProtocols key in your application Info.plist file or via the Info tab of your project settings.

  |Communication Protocol|Zebra Scanner|
  |-----|-----|
  |com.motorolasolutions.CS4070_ssi|CS4070|
  |com.zebra.scanner.SSI|RFD8500|
  |com.motorolasolutions.scanner|RFD8500|

## Methods:
* **setEnabled(isEnabled)**: Enable or disable active scanners
* **getActiveScanners(callback)**: Returns the list of active scanners in callback function

## Usage
```javascript
import useZebraScanner from 'react-native-scanner-zebra';

// Called when barcode is scanned
const onScan = useCallback((barcode, scannerId) => {
	// Handle the barcode
}, []);

// Called when scanner event occurred
const onEvent = useCallback((event, scannerId) => {
	// Handle the event
}, []);

const { setEnabled, getActiveScanners } = useZebraScanner(onScan, onEvent);

```

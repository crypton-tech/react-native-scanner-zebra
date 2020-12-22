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

## Usage
```javascript
import useZebraScanner from 'react-native-scanner-zebra';

const onScan = useCallback((barcode, scannerId) => {
	// Handle the barcode
}, []);

useZebraScanner(onScan);

```

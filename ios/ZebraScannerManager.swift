//
//  ZebraScannerManager.swift
//
//  Created by Crypton
//  Copyright © 2020 Crypton. All rights reserved.
//

import Foundation

struct Scanner {
    var scannerId: Int32
    var name: String
}

class WeakReference<T: AnyObject> {
    weak var value: T?

    init(value: T) {
        self.value = value
    }

    func release() {
        value = nil
    }
}

@objc protocol ScannerEventListener {
    func onEvent(event: String, data: NSDictionary)
}

class ZebraScannerManager: NSObject, ISbtSdkApiDelegate {
    static let instance: ZebraScannerManager = ZebraScannerManager()

    private var apiInstance: ISbtSdkApi! = nil
    private var availableScanners: [Scanner] = []
    private var isLoaded: Bool = false
    private var listeners: [WeakReference<ScannerEventListener>] = []

    func initialize() {
        if isLoaded == false {
            self.isLoaded = true
            self.apiInstance = SbtSdkFactory.createSbtSdkApiInstance()
            self.apiInstance.sbtSetDelegate(self)
            self.setupApi()
            print("Scanner initialized")
        }
    }

    func getActiveScanners() -> [NSDictionary] {
        var scanners: [NSDictionary] = []
        for item in availableScanners {
            var scannerDict: [String: Any] = [:]
            scannerDict["id"] = item.scannerId
            scannerDict["name"] = item.name
            scanners.append(scannerDict as NSDictionary)
        }

        return scanners
    }

    func getSupportedEvents() -> [String] {
        return [
            "scanner-appeared",
            "scanner-disappeared",
            "scanner-connected",
            "scanner-disconnected",
            "scanner-barcode",
            "scanner-barcode-data"
        ]
    }

    func setEnabled(_ isEnabled: Bool) {
        for item in availableScanners {
            enableScanner(item.scannerId, isEnabled: isEnabled)
        }
    }

    func addListener(_ listener: ScannerEventListener) {
        // if listeners.compactMap({ $0.value }).contains(listener) { return }
        listeners.append(WeakReference(value: listener))
    }

    // Private Functions
    fileprivate func setupApi() {
        apiInstance.sbtSetOperationalMode(Int32(SBT_OPMODE_BTLE))
        apiInstance.sbtSubsribe(forEvents: Int32(SBT_EVENT_SCANNER_APPEARANCE |
                                                    SBT_EVENT_SCANNER_DISAPPEARANCE | SBT_EVENT_SESSION_ESTABLISHMENT |
                                                    SBT_EVENT_SESSION_TERMINATION | SBT_EVENT_BARCODE))
        apiInstance.sbtEnableAvailableScannersDetection(true)
        
        var scanners = NSMutableArray()
        let scannerPointer = AutoreleasingUnsafeMutablePointer<NSMutableArray?>.init(&scanners)
        apiInstance.sbtGetActiveScannersList(scannerPointer)
        
        for item in scanners {
            let scanner = item as! SbtScannerInfo
            addAvailableScanner(scanner.getScannerID(), name: scanner.getScannerName())
        }
    }

    fileprivate func addAvailableScanner(_ scannerId: Int32, name: String) {
        self.removeAvailableScanner(scannerId)
        self.availableScanners.append(Scanner(scannerId: scannerId, name: name))
        
        print("Scanner Found", scannerId, name)
    }

    fileprivate func removeAvailableScanner(_ scannerId: Int32) {
        if let index = self.availableScanners.firstIndex(where: {$0.scannerId == scannerId}) {
            self.availableScanners.remove(at: index)
        }
    }

    fileprivate func sendEvent(event: String, data: NSDictionary) {
        listeners.forEach({ $0.value?.onEvent(event: event, data: data)})
    }

    fileprivate func connectToScanner(_ scannerId: Int32) {
        let result: SBT_RESULT = apiInstance.sbtEstablishCommunicationSession(scannerId)
        if result == SBT_RESULT_SUCCESS {
            print("Connected to scanner")
        } else {
            print("Failed: Connect to scanner")
        }
    }

    fileprivate func disconnectToScanner(_ scannerId: Int32) {
        let result: SBT_RESULT = apiInstance.sbtEstablishCommunicationSession(scannerId)
        if result == SBT_RESULT_SUCCESS {
            print("Disconnected from scanner")
        } else {
            print("Failed: Disconnect from scanner")
        }
    }

    fileprivate func automaticReConnectToScanner(_ scannerId: Int32) {
        let result: SBT_RESULT = apiInstance.sbtEnableAutomaticSessionReestablishment(true,
                                                                                      forScanner: scannerId)
        if result == SBT_RESULT_SUCCESS {
            print("Scanner updated for auto reconnect")
        } else {
            print("Failed: Update scanner for auto reconnect")
        }
    }

    fileprivate func enableScanningCapability(_ scannerId: Int32) {
        let xml = String(format: "<inArgs><scannerID>%d</scannerID></inArgs>", scannerId)
        let result = apiInstance.sbtExecuteCommand(Int32(SBT_DEVICE_SCAN_ENABLE), aInXML: xml,
                                                   aOutXML: nil, forScanner: scannerId)
        if result == SBT_RESULT_SUCCESS {
            print("Scanner enabled for scanning")
        } else {
            print("Failed: Enable scanner for scanning")
        }
    }

    fileprivate func disableScanningCapability(_ scannerId: Int32) {
        let xml = String(format: "<inArgs><scannerID>%d</scannerID></inArgs>", scannerId)
        let result = apiInstance.sbtExecuteCommand(Int32(SBT_DEVICE_SCAN_DISABLE), aInXML: xml,
                                                   aOutXML: nil, forScanner: scannerId)
        if result == SBT_RESULT_SUCCESS {
            print("Scanner disabled for scanning")
        } else {
            print("Failed: Disable scanner for scanning")
        }
    }

    fileprivate func enableScanner(_ scannerId: Int32, isEnabled: Bool) {
        let command: Int32 = isEnabled ? Int32(SBT_DEVICE_PULL_TRIGGER) : Int32(SBT_DEVICE_RELEASE_TRIGGER)
        let xml = String(format: "<inArgs><scannerID>%d</scannerID></inArgs>", scannerId)
        let result = apiInstance.sbtExecuteCommand(command, aInXML: xml,
                                                   aOutXML: nil, forScanner: scannerId)
        if result == SBT_RESULT_SUCCESS {
            print(isEnabled ? "Scanner Enabled" : "Scanner Disabled")
        } else {
            print(isEnabled ? "Failed: Enable scanner" : "Failed: Disable scanner")
        }
    }

    // Delegate functions
    func sbtEventScannerAppeared(_ availableScanner: SbtScannerInfo!) {
        if let device = availableScanner, let scannerName = device.getScannerName() {
            let scannerId: Int32 = device.getScannerID()
            self.connectToScanner(scannerId)
            self.addAvailableScanner(scannerId, name: scannerName)

            self.sendEvent(event: "scanner-appeared", data: ["id": scannerId])
        }
    }

    func sbtEventScannerDisappeared(_ scannerId: Int32) {
        self.disconnectToScanner(scannerId)
        self.removeAvailableScanner(scannerId)

        self.sendEvent(event: "scanner-disappeared", data: ["id": scannerId])
    }

    func sbtEventCommunicationSessionEstablished(_ activeScanner: SbtScannerInfo!) {
        if let device = activeScanner {
            self.sendEvent(event: "scanner-connected", data: ["id": device.getScannerID()])
        }
    }

    func sbtEventCommunicationSessionTerminated(_ scannerId: Int32) {
        self.sendEvent(event: "scanner-disconnected", data: ["id": scannerId])
    }

    func sbtEventBarcode(_ barcodeData: String!, barcodeType: Int32, fromScanner scannerId: Int32) {
        if let barcode = barcodeData {
            self.sendEvent(event: "scanner-barcode",
                           data: ["id": scannerId, "barcode": barcode, "type": barcodeType])
        }
    }

    func sbtEventBarcodeData(_ barcodeData: Data!, barcodeType: Int32, fromScanner scannerId: Int32) {
        if let data = barcodeData {
            self.sendEvent(event: "scanner-barcode-data",
                           data: ["id": scannerId, "barcode": data as NSData, "type": barcodeType])
        }
    }

    func sbtEventFirmwareUpdate(_ fwUpdateEventObj: FirmwareUpdateEvent!) {
    }

    func sbtEventImage(_ imageData: Data!, fromScanner scannerId: Int32) {
    }

    func sbtEventVideo(_ videoFrame: Data!, fromScanner scannerId: Int32) {
    }
}

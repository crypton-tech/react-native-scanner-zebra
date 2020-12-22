//
//  ZebraScanner.swift
//  ZebraScanner
//
//  Copyright © 2020 Crypton. All rights reserved.
//

import Foundation

@objc(ZebraScanner)
class ZebraScanner: RCTEventEmitter, ScannerEventListener {
    override init() {
        super.init()
        ZebraScannerManager.instance.initialize()
        ZebraScannerManager.instance.addListener(self)
    }

    @objc open func getActiveScanners() -> [NSDictionary] {
        return ZebraScannerManager.instance.getActiveScanners()
    }

    @objc
    override static func requiresMainQueueSetup() -> Bool {
        return false
    }

    override func supportedEvents() -> [String]! {
        return ZebraScannerManager.instance.getSupportedEvents()
    }

    func onEvent(event: String, data: NSDictionary) {
        self.sendEvent(withName: event, body: data)
    }
}

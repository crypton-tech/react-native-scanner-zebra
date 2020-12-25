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

    @objc(getActiveScanners:)
    open func getActiveScanners(_ callback: RCTResponseSenderBlock) {
        let scanners: [NSDictionary] = ZebraScannerManager.instance.getActiveScanners()
        callback([scanners])
    }

    @objc(setEnabled:)
    open func setEnabled(isEnabled: Bool) {
        ZebraScannerManager.instance.setEnabled(isEnabled)
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

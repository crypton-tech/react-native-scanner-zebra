//
//  ZebraScanner.m
//  ZebraScanner
//
//  Copyright © 2020 Crypton. All rights reserved.
//

#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>

@interface RCT_EXTERN_MODULE(ZebraScanner, RCTEventEmitter)
    RCT_EXTERN_METHOD(setEnabled: (BOOL) isEnabled)
    RCT_EXTERN_METHOD(getActiveScanners: (RCTResponseSenderBlock) callback)
@end

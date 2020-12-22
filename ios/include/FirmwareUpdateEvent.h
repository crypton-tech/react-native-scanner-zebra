//
//  FirmwareUpdateEvent.h
//  ScannerSDKApp
//
//  Created by pqj647 on 6/7/16.
//  Copyright © 2016 Alexei Igumnov. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SbtScannerInfo.h"
#import "SbtSdkDefs.h"

@interface FirmwareUpdateEvent : NSObject
    /**
     Scanner that triggered the event
     **/
    @property (nonatomic, retain) SbtScannerInfo *scannerInfo;
    /*
     Maximum number of records contained in the firmware update file
     */
    @property(readonly) int maxRecords;
     /**Software component number that download has started.     */
    @property(readonly) int swComponent;
    /*
     Record number that is being download. This will be available in SCANNER_UF_DL_PROGRESS
     */
    @property(readonly) int currentRecord;
    /*
     Size of the
     */
    @property(readonly) int size;
    /*
     Status of the event.
     */
    @property(readonly) SBT_FW_UPDATE_RESULT status;

- (instancetype)initWithScannerInfo:(SbtScannerInfo*)_scannerInfo withRecords:(int)_maxRecords withSWComponenet:(int)_swComponent withCurrentRecord:(int)_currentRecord withStatus:(SBT_FW_UPDATE_RESULT)_status;

@end

/******************************************************************************
 *
 *       Copyright Zebra Technologies Corporation. 2013 - 2015
 *
 *       The copyright notice above does not evidence any
 *       actual or intended publication of such source code.
 *       The code contains Zebra Technologies
 *       Confidential Proprietary Information.
 *
 *
 *  Description:   ISbtSdkApiDelegate.h
 *
 *  Notes:
 *
 ******************************************************************************/

#import <Foundation/Foundation.h>
#import "SbtScannerInfo.h"
#import "FirmwareUpdateEvent.h"

@protocol ISbtSdkApiDelegate <NSObject>

- (void)sbtEventScannerAppeared:(SbtScannerInfo*)availableScanner;
- (void)sbtEventScannerDisappeared:(int)scannerID;
- (void)sbtEventCommunicationSessionEstablished:(SbtScannerInfo*)activeScanner;
- (void)sbtEventCommunicationSessionTerminated:(int)scannerID;
- (void)sbtEventBarcode:(NSString*)barcodeData barcodeType:(int)barcodeType fromScanner:(int)scannerID;
- (void)sbtEventBarcodeData:(NSData*)barcodeData barcodeType:(int)barcodeType fromScanner:(int)scannerID;
- (void)sbtEventFirmwareUpdate:(FirmwareUpdateEvent*)fwUpdateEventObj;

/* TBD */
- (void)sbtEventImage:(NSData*)imageData fromScanner:(int)scannerID;
/* TBD */
- (void)sbtEventVideo:(NSData*)videoFrame fromScanner:(int)scannerID;

@end

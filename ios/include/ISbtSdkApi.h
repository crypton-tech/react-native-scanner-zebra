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
 *  Description:   ISbtSdkApi.h
 *
 *  Notes:
 *
 ******************************************************************************/

#import <Foundation/Foundation.h>

#import "SbtSdkDefs.h"
#import "ISbtSdkApiDelegate.h"
#import <UIKit/UIKit.h>

@protocol ISbtSdkApi <NSObject>

- (SBT_RESULT) sbtSetDelegate:(id<ISbtSdkApiDelegate>)delegate;
- (NSString*) sbtGetVersion;
- (SBT_RESULT) sbtSetOperationalMode:(int)operationalMode;
- (SBT_RESULT) sbtSubsribeForEvents:(int)sdkEventsMask;
- (SBT_RESULT) sbtUnsubsribeForEvents:(int)sdkEventsMask;
/* note: App is responsible for allocation and deallocation of array */
- (SBT_RESULT) sbtGetAvailableScannersList:(NSMutableArray**)availableScannersList;
/* note: App is responsible for allocation and deallocation of array */
- (SBT_RESULT) sbtGetActiveScannersList:(NSMutableArray**)activeScannersList;
- (SBT_RESULT) sbtEstablishCommunicationSession:(int)scannerID;
- (SBT_RESULT) sbtTerminateCommunicationSession:(int)scannerID;
- (SBT_RESULT) sbtEnableAvailableScannersDetection:(BOOL)enable;
- (SBT_RESULT) sbtEnableBluetoothScannerDiscovery:(BOOL)enable;
- (SBT_RESULT) sbtEnableAutomaticSessionReestablishment:(BOOL)enable forScanner:(int)scannerID;
- (SBT_RESULT) sbtExecuteCommand:(int)opCode aInXML:(NSString*)inXML aOutXML:(NSMutableString**)outXML forScanner:(int)scannerID;
- (SBT_RESULT) sbtLedControl:(BOOL)enable aLedCode:(int)ledCode forScanner:(int)scannerID;
- (SBT_RESULT) sbtBeepControl:(int)beepCode forScanner:(int)scannerID;
- (void) sbtSetBTAddress:(NSString*)btAdd;
- (UIImage*) sbtGetPairingBarcode:(BARCODE_TYPE)barcodeType withComProtocol:(STC_COM_PROTOCOL)comProtocol withSetDefaultStatus:(SETDEFAULT_STATUS)setDefaultsStatus withBTAddress:(NSString*)btAddress withImageFrame:(CGRect)imageFrame;
- (UIImage*) sbtGetPairingBarcode:(BARCODE_TYPE)barcodeType withComProtocol:(STC_COM_PROTOCOL)comProtocol withSetDefaultStatus:(SETDEFAULT_STATUS)setDefaultsStatus withImageFrame:(CGRect)imageFrame;

@end

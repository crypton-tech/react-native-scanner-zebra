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
 *  Description:   SbtScannerInfo.h
 *
 *  Notes:
 *
 ******************************************************************************/

#import <Foundation/Foundation.h>

@interface SbtScannerInfo : NSObject
{
    int m_ScannerID; /* SDK assigned unique id */
    int m_ConnectionType; /* mfi, btle */
    BOOL m_AutoCommunicationSessionReestablishment;
    BOOL m_Active; /* communication session is established */
    BOOL m_Available;
    NSString *m_ScannerName;
    int m_ScannerModel;
}

- (id)init;
- (void)dealloc;

- (void)setScannerID:(int)scannerID;
- (void)setConnectionType:(int)connectionType;
- (void)setAutoCommunicationSessionReestablishment:(BOOL)enable;
- (void)setActive:(BOOL)active;
- (void)setAvailable:(BOOL)available;
- (void)setScannerName:(NSString*)scannerName;
- (void)setScannerModel:(int)scannerModel;

- (int)getScannerID;
- (int)getConnectionType;
- (BOOL)getAutoCommunicationSessionReestablishment;
- (BOOL)isActive;
- (BOOL)isAvailable;
- (NSString*)getScannerName;
- (int)getScannerModel;

@property(nonatomic, retain) NSString *firmwareVersion;
@property(nonatomic, retain) NSString *mFD;
@property(nonatomic, retain) NSString *serialNo;
@property(nonatomic, retain) NSString *scannerModelString;

@end

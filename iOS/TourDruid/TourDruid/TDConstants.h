//
//  TDConstants.h
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

@interface TDConstants : NSObject
+ (void) buildNames;
+ (void) buildURLs;
+ (NSString *)nameFromId:(NSNumber *)buildingID;
+ (NSInteger)numberOfBuildings;
+ (UIImage *) imageFromId:(NSNumber *)imageId;
+ (UIImage *) imageFromName:(NSString *)building;
+ (NSString *) urlFromName:(NSString *)buildingId;
+ (MKCoordinateRegion) regionFromName:(NSString *)building;
+ (UIImage *) mapFromName:(NSString *)building;
+ (void) buildMaps;
+ (void) buildImages;
@end

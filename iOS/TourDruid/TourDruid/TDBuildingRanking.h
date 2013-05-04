//
//  TDBuildingRanking.h
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TDBuildingRanking : NSObject
@property (nonatomic) NSString *name;
@property (nonatomic) NSNumber *confidence;
@property (nonatomic) NSNumber *buildingId;
- (id) init:(NSNumber *)buildingID confidence:(NSNumber *)confidence;
@end

//
//  TDConstants.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "TDConstants.h"

@implementation TDConstants
NSArray *_names;

+ (void) buildNames
{
    _names = [[NSArray alloc ] initWithObjects:@"Alma Mater" ,@"Butler", @"CEPSR", @"CURL", @"Hamilton",   @"Havemayer", @"Journalism", @"Law", @"Lerner", @"Lion", @"Low", @"Mathematics", @"Mudd", @"Noco", @"Pan", @"Pupin", @"Thinker", nil];
}

+ (NSString *)nameFromId:(NSNumber *)buildingID
{
    if(_names == nil) {
        [self buildNames];
    }

    if ([buildingID integerValue] > [_names count]) {
        return nil;
    } else
        return (NSString *)[_names objectAtIndex:[buildingID integerValue]];
}

+ (NSInteger)numberOfBuildings
{
    if(_names == nil) {
        [self buildNames];
    }
    return [_names count];
}
@end

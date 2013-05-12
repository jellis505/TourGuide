//
//  TDConstants.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "TDConstants.h"
#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
#define METERS_PER_MILE 1609.344
@implementation TDConstants
NSArray *_names;
NSDictionary *_images;
NSDictionary *_urls;
NSDictionary *_maps;

+ (void) buildNames
{
    _names = [[NSArray alloc ] initWithObjects:@"Alma Mater" ,@"Butler Library", @"CEPSR", @"Curl", @"Hamilton",   @"Havemayer", @"Journalism", @"Law", @"Lerner", @"Lion", @"Low", @"Mathematics", @"Mudd", @"Noco", @"Pan", @"Pupin", @"Thinker", nil];
}

+ (void) buildImages
{
    if (_names == nil) {
        [self buildNames];
    }
    
    NSArray *imageNames = [[NSArray alloc ] initWithObjects:@"almamater1.jpg" ,@"butler1.jpg", @"CEPSR1.jpg", @"curl1.jpg", @"hamilton1.jpg",   @"havemayer.png", @"journalism1.jpg", @"law1.png", @"lerner1.JPG", @"lion1.jpg", @"low1.jpg", @"mathematics1.jpg", @"mudd1.jpg", @"noco1.jpg", @"pan1.JPG", @"pupin1.png", @"thinker1.jpg", nil];

    NSMutableArray *tmp_images = [[NSMutableArray alloc] init];
    for (NSString *name in imageNames) {
        NSLog(@"yes");
        [tmp_images addObject:[UIImage imageNamed:name]];
    }
    _images = [[NSDictionary alloc] initWithObjects:tmp_images forKeys:_names];
}

+ (void) buildMaps
{
    if (_names == nil) {
        [self buildNames];
    }

    NSArray *mapNames = [[NSArray alloc ] initWithObjects:@"alma_map.jpg" ,@"butler_map.jpg", @"cepsr_map.jpg", @"curl_map.jpg", @"hamilton_map.jpg",   @"havemayer_map.jpg", @"journalism_map.jpg", @"law_map.jpg", @"lerner_map.jpg", @"lion_map.jpg", @"low_map.jpg", @"math_map.jpg", @"mudd_map.jpg", @"noco_map.jpg", @"pan_map.jpg", @"pupin_map.jpg", @"thinker_map.jpg", nil];

        NSMutableArray *tmp_images = [[NSMutableArray alloc] init];
        for (NSString *name in mapNames) {
            [tmp_images addObject:[UIImage imageNamed:name]];
        }
    _maps = [[NSDictionary alloc] initWithObjects:tmp_images forKeys:_names];
}

+ (NSString *)nameFromId:(NSNumber *)buildingID
{
    if (_names == nil) {
        [self buildNames];
    }

    if ([buildingID integerValue] > [_names count]) {
        return nil;
    } else
        return (NSString *)[_names objectAtIndex:[buildingID integerValue]];
}

+ (UIImage *) mapFromName:(NSString *)building
{
    if (_maps == nil) {
        [self buildMaps];
    }


    return (UIImage *)[_maps objectForKey:building];
}
+ (UIImage *) imageFromName:(NSString *)building
{
    if (_images == nil) {
        [self buildImages];
    }


    return (UIImage *)[_images objectForKey:building];
}

+ (UIImage *) imageFromId:(NSNumber *)buildingId
{
    if (_images == nil) {
        [self buildImages];
    }


    return (UIImage *)[_images objectForKey:(NSNumber *)[_names objectAtIndex:[buildingId integerValue]]];
}

+ (NSInteger)numberOfBuildings
{
    if(_names == nil) {
        [self buildNames];
    }
    return [_names count];
}

+ (void) buildURLs
{
    if (_names == nil) {
        [self buildNames];
    }

    NSArray *urlStrings = [[NSArray alloc ] initWithObjects:@"http://www.wikicu.com/Alma_Mater" ,@"http://www.wikicu.com/Butler_Library", @"http://www.wikicu.com/CEPSR", @"http://www.wikicu.com/Curl", @"http://www.wikicu.com/Hamilton_Hall",   @"http://www.wikicu.com/Havemeyer_Hall", @"http://www.wikicu.com/Journalism", @"http://www.wikicu.com/Law", @"http://www.wikicu.com/Lerner", @"http://www.wikicu.com/Scholar%27s_Lion", @"http://www.wikicu.com/Low_Library", @"http://www.wikicu.com/Mathematics_Hall", @"http://www.wikicu.com/Mudd", @"http://www.wikicu.com/Northwest_Science_Building", @"http://www.wikicu.com/The_Great_God_Pan", @"http://www.wikicu.com/Pupin_Physics_Laboratories", @"http://www.wikicu.com/The_Thinker", nil];

    _urls = [[NSDictionary alloc] initWithObjects:urlStrings forKeys:_names];
}

+ (NSString *) urlFromName:(NSString *)buildingId
{
    if (_urls == nil) {
        [self buildURLs];
    }
    
    return (NSString *)[_urls objectForKey:buildingId];
}

+ (MKCoordinateRegion) regionFromName:(NSString *)building
{
    if (_names == nil) {
        [self buildNames];
    }

    CLLocationCoordinate2D zoomLocation;
    zoomLocation.latitude = 39.281516;
    zoomLocation.longitude= -76.580806;

    MKCoordinateRegion viewRegion = MKCoordinateRegionMakeWithDistance(zoomLocation, 0.5*METERS_PER_MILE, 0.5*METERS_PER_MILE);

    return viewRegion;
}
@end

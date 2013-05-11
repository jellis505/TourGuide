//
//  InfoViewController.h
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/10/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
@class MapViewController;
@interface InfoViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIWebView *webView;
@property (weak, nonatomic) MapViewController *mapView;
- (void)setBuildingName:(NSString *)buildingName;
@end

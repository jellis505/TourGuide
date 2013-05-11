//
//  WrongAnswerViewController.h
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/4/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import <UIKit/UIKit.h>
@class TDResponse;
@class InfoViewController;
@interface WrongAnswerViewController : UITableViewController
@property (nonatomic) InfoViewController *infoView;
-(void)setResponse:(TDResponse *)response;
@end

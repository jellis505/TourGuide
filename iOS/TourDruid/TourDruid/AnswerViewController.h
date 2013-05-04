//
//  AnswerViewController.h
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import <UIKit/UIKit.h>
@class TDResponse;

@interface AnswerViewController : UIViewController<UITableViewDelegate, UITableViewDataSource>
- (BOOL)loadResponseViewFromController:(UIViewController*) controller
                              response:(TDResponse *)response;
-(void) setRanking:(NSArray *)ranking;
@end

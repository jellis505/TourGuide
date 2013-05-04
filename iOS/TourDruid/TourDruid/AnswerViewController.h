//
//  AnswerViewController.h
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AnswerViewController : UIViewController<UITableViewDelegate, UITableViewDataSource>
- (BOOL)loadResponseViewFromController:(UIViewController*) controller
                              ranking:(NSArray *)ranking;
-(void) setRanking:(NSArray *)ranking;
@end

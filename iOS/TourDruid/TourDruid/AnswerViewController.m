//
//  AnswerViewController.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "AnswerViewController.h"
#import "TDBuildingRanking.h"

@interface AnswerViewController () {
    @private
    NSArray *_ranking;
}

@end

@implementation AnswerViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    UIStoryboard *sb = [UIStoryboard storyboardWithName:@"MainStoryboard_iPhone" bundle:nil];
    self = [sb instantiateViewControllerWithIdentifier:@"ResultView"];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSLog(@"herheheh");
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView*)tableView numberOfRowsInSection:(NSInteger)section {
    return [_ranking count];
}

-(void) setRanking:(NSArray *)ranking {
    _ranking = ranking;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellId = @"identifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellId];

    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:cellId];
    }
    TDBuildingRanking *rank = [_ranking objectAtIndex:indexPath.row];
    cell.textLabel.text = [rank name];
    double percentage = 100 * [[rank confidence] doubleValue];

    cell.detailTextLabel.text = [NSString stringWithFormat:@"%@%%",[[NSNumber numberWithDouble:percentage] stringValue]];
     return cell;
}

- (BOOL)loadResponseViewFromController:(UIViewController*) controller
                              ranking:(NSArray *)ranking
{
    _ranking = ranking;
    [controller presentViewController:self animated:YES completion:nil];
    return YES;
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
    /*
     <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:@"<#Nib name#>" bundle:nil];
     // ...
     // Pass the selected object to the new view controller.
     [self.navigationController pushViewController:detailViewController animated:YES];
     */
    NSLog(@"selected");
}
@end

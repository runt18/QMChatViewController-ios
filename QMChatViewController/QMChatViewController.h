//
//  QMChatViewController.h
//  QMChatViewController
//
//  Created by Andrey Ivanov on 06.04.15.
//  Copyright (c) 2015 QuickBlox Team. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "QMChatCollectionView.h"
#import "QMChatCollectionViewDelegateFlowLayout.h"
#import "QMChatCollectionViewFlowLayout.h"
#import "QMChatActionsHandler.h"
#import "QMInputToolbar.h"
#import <Quickblox/Quickblox.h>

#import "QMChatContactRequestCell.h"
#import "QMChatIncomingCell.h"
#import "QMChatOutgoingCell.h"
#import "QMChatNotificationCell.h"
#import "QMChatAttachmentIncomingCell.h"
#import "QMChatAttachmentOutgoingCell.h"

@interface QMChatViewController : UIViewController <QMChatCollectionViewDataSource, QMChatCollectionViewDelegateFlowLayout, UITextViewDelegate>

/**
 *  Cell's contact request delegate.
 */
@property (weak, nonatomic) id <QMChatActionsHandler> actionsHandler;

/**
 *  Returns the collection view object managed by this view controller.
 *  This view controller is the collection view's data source and delegate.
 */
@property (weak, nonatomic, readonly) QMChatCollectionView *collectionView;

/**
 *  Returns the input toolbar view object managed by this view controller.
 *  This view controller is the toolbar's delegate.
 */
@property (weak, nonatomic, readonly) QMInputToolbar *inputToolbar;

/**
 *  The display name of the current user who is sending messages.
 *
 *  @discussion This value does not have to be unique. This value must not be `nil`.
 */
@property (copy, nonatomic) NSString *senderDisplayName;

/**
 *  The string identifier that uniquely identifies the current user sending messages.
 *
 *  @discussion This property is used to determine if a message is incoming or outgoing.
 *  All message data objects returned by `collectionView:messageDataForItemAtIndexPath:` are
 *  checked against this identifier. This value must not be `nil`.
 */
@property (assign, nonatomic) NSUInteger senderID;

/**
 *  The time interval that used to split messages between sections.
 *
 *  @discussion You should set time interval in seconds with '- (NSTimeInterval)timeIntervalBetweenSections' data source method.
 *  The messages that have dateSent difference from the first message in section not greater then the one you set,
 *  will appear in one section under one date.
 */
@property (assign, nonatomic) NSTimeInterval timeIntervalBetweenSections;

/**
 *  Specifies whether or not the view controller should automatically scroll to the most recent message
 *  when the view appears and when sending, receiving, and composing a new message.
 *
 *  @discussion The default value is `YES`, which allows the view controller to scroll automatically to the most recent message.
 *  Set to `NO` if you want to manage scrolling yourself.
 */
@property (assign, nonatomic) BOOL automaticallyScrollsToMostRecentMessage;

/**
 *  Specifies whether or not the view controller should show the typing indicator for an incoming message.
 *
 *  @discussion Setting this property to `YES` will animate showing the typing indicator immediately.
 *  Setting this property to `NO` will animate hiding the typing indicator immediately. You will need to scroll
 *  to the bottom of the collection view in order to see the typing indicator. You may use `scrollToBottomAnimated:` for this.
 */
@property (assign, nonatomic) BOOL showTypingIndicator;

/**
 *  Specifies an additional inset amount to be added to the collectionView's contentInsets.top value.
 *
 *  @discussion Use this property to adjust the top content inset to account for a custom subview at the top of your view controller.
 */
@property (assign, nonatomic) CGFloat topContentAdditionalInset;

/**
 *  Chat message items.
 */
@property (strong, nonatomic) NSMutableArray *items;

/**
 *  Method to create chat message text attributed string. Have to be overriden in subclasses.
 *
 *  @param messageItem Chat message instance.
 *
 *  @return Configured attributed string.
 */
- (NSAttributedString *)attributedStringForItem:(QBChatMessage *)messageItem;

/**
 *  Method to create chat message top label attributed string (Usually - chat message owner name). Have to be overriden in subclasses.
 *
 *  @param messageItem Chat message instance.
 *
 *  @return Configured attributed string.
 */
- (NSAttributedString *)topLabelAttributedStringForItem:(QBChatMessage *)messageItem;

/**
 *  Method to create chat message bottom label attributed string (Usually - chat message date sent). Have to be overriden in subclasses.
 *
 *  @param messageItem Chat message instance.
 *
 *  @return Configured attributed string.
 */
- (NSAttributedString *)bottomLabelAttributedStringForItem:(QBChatMessage *)messageItem;

/**
 *  Collection Cell View class for specific message. Have to be overriden in subclasses. Defaults cells are supplied with QMChatViewController.
 *
 *  @param item Chat message instance.
 *
 *  @return Collection Cell View Class
 */
- (Class)viewClassForItem:(QBChatMessage *)item;

- (void)collectionView:(QMChatCollectionView *)collectionView configureCell:(UICollectionViewCell *)cell forIndexPath:(NSIndexPath *)indexPath;

#pragma mark - Class methods

/**
 *  Returns the `UINib` object initialized for a `QMChatViewController`.
 *
 *  @return The initialized `UINib` object or `nil` if there were errors during initialization
 *  or the nib file could not be located.
 *
 *  @discussion You may override this method to provide a customized nib. If you do,
 *  you should also override `messagesViewController` to return your
 *  view controller loaded from your custom nib.
 */
+ (UINib *)nib;

/**
 *  Creates and returns a new `QMChatViewController` object.
 *
 *  @discussion This is the designated initializer for programmatic instantiation.
 *
 *  @return An initialized `QMChatViewController` object if successful, `nil` otherwise.
 */
+ (instancetype)messagesViewController;

#pragma mark - Messages view controller

/**
 *  This method is called when the user taps the send button on the inputToolbar
 *  after composing a message with the specified data.
 *
 *  @param button            The send button that was pressed by the user.
 *  @param text              The message text.
 *  @param senderId          The message sender identifier.
 *  @param senderDisplayName The message sender display name.
 *  @param date              The message date.
 */
- (void)didPressSendButton:(UIButton *)button
           withMessageText:(NSString *)text
                  senderId:(NSUInteger)senderId
         senderDisplayName:(NSString *)senderDisplayName
                      date:(NSDate *)date;

/**
 *  This method is called when the user taps the accessory button on the `inputToolbar`.
 *
 *  @param sender The accessory button that was pressed by the user.
 */
- (void)didPressAccessoryButton:(UIButton *)sender;

- (void)didPickAttachmentImage:(UIImage *)image;

/**
 *  Animates the sending of a new message. See `finishSendingMessageAnimated:` for more details.
 *
 *  @see `finishSendingMessageAnimated:`.
 */
- (void)finishSendingMessage;

/**
 *  Completes the "sending" of a new message by resetting the `inputToolbar`, adding a new collection view cell in the collection view,
 *  reloading the collection view, and scrolling to the newly sent message as specified by `automaticallyScrollsToMostRecentMessage`.
 *  Scrolling to the new message can be animated as specified by the animated parameter.
 *
 *  @param animated Specifies whether the sending of a message should be animated or not. Pass `YES` to animate changes, `NO` otherwise.
 *
 *  @discussion You should call this method at the end of `didPressSendButton: withMessageText: senderId: senderDisplayName: date`
 *  after adding the new message to your data source and performing any related tasks.
 *
 *  @see `automaticallyScrollsToMostRecentMessage`.
 */
- (void)finishSendingMessageAnimated:(BOOL)animated;

/**
 *  Animates the receiving of a new message. See `finishReceivingMessageAnimated:` for more details.
 *
 *  @see `finishReceivingMessageAnimated:`.
 */
- (void)finishReceivingMessage;

/**
 *  Completes the "receiving" of a new message by showing the typing indicator, adding a new collection view cell in the collection view,
 *  reloading the collection view, and scrolling to the newly sent message as specified by `automaticallyScrollsToMostRecentMessage`.
 *  Scrolling to the new message can be animated as specified by the animated parameter.
 *
 *  @param animated Specifies whether the receiving of a message should be animated or not. Pass `YES` to animate changes, `NO` otherwise.
 *
 *  @discussion You should call this method after adding a new "received" message to your data source and performing any related tasks.
 *
 *  @see `automaticallyScrollsToMostRecentMessage`.
 */
- (void)finishReceivingMessageAnimated:(BOOL)animated;

/**
 *  Scrolls the collection view such that the bottom most cell is completely visible, above the `inputToolbar`.
 *
 *  @param animated Pass `YES` if you want to animate scrolling, `NO` if it should be immediate.
 */
- (void)scrollToBottomAnimated:(BOOL)animated;

#pragma mark - Helpers

/**
 *  Message for index path.
 *
 *  @param indexPath    index path to find message
 *
 *  @return QBChatMessage instance that conforms to indexPath
 */
- (QBChatMessage *)messageForIndexPath:(NSIndexPath *)indexPath;

/**
 *  Index path for message.
 *
 *  @param message  message to return index path
 *
 *  @return NSIndexPath instance that conforms message or nil if not found
 */
- (NSIndexPath *)indexPathForMessage:(QBChatMessage *)message;

@end

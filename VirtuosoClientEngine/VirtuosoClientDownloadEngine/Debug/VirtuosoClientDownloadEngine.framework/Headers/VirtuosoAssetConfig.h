/*!
 *  @header Virtuoso Asset Configuration
 *
 *  PENTHERA CONFIDENTIAL
 *
 *  Notice: This file is the property of Penthera Inc.
 *  The concepts contained herein are proprietary to Penthera Inc.
 *  and may be covered by U.S. and/or foreign patents and/or patent
 *  applications, and are protected by trade secret or copyright law.
 *  Distributing and/or reproducing this information is forbidden unless
 *  prior written permission is obtained from Penthera Inc.
 *
 *  @copyright (c) 2018 Penthera Inc. All Rights Reserved.
 *
 */

#ifndef VirtuosoAssetConfig_h
#define VirtuosoAssetConfig_h

#import <Foundation/Foundation.h>
#import "VirtuosoConstants.h"

@class VirtuosoAncillaryFile;
@class VirtuosoAdsProvider;

/*!
 *  @abstract Use this class to configure settings used when creating an Asset.
 *
 *  @discussion This class is used to configure the Asset during creation.
 *              Create an instance then set other properties as needed.
 *
 */
@interface VirtuosoAssetConfig : NSObject

/*!
 *  @abstract Where this asset exists on the Internet
 *
 *  @discussion The asset URL is the addressable location on the Internet.
 *              It must include any required security or CDN tokens.
 *
 *              If your CDN uses dynamic URLs or another method where URLs change over time, Virtuoso
 *              may need to issue a network request to get a 'fresh' URL.  In that case, this method
 *              will block during this network request.
 */
@property (nonatomic, copy, readonly)NSString* _Nonnull assetURL;

/*!
 *  @abstract A unique identifier that you provide when instantiating this asset
 *
 *  @discussion Virtuoso uses the assetID in log events and for remote delete/wipe requests.
 */
@property (nonatomic, copy, readonly)NSString* _Nonnull assetID;

/*!
 *  @abstract A human-readable description for this asset
 *
 *  @discussion Virtuoso does not use this internally, but does include it in logging output.
 *              You provided this value when instantiating this asset.
 */
@property (nonatomic, copy, readonly)NSString* _Nonnull assetDescription;

/*!
 *  @abstract The asset type
 */
@property (nonatomic, assign, readonly)kVDE_AssetType assetType;

/*
 *  @abstract The asset protection type identified during asset creation.
 *
 *  @discussion In some configurations, special handling is required in order to download and play assets.
 *              Most of the time, you should pass the default value (kVDE_AssetProtectionTypePassthrough).  If
 *              instructed by Penthera support, you may be required to pass another value when the asset is created.
 */
@property (nonatomic, assign)kVDE_AssetProtectionType protectionType;

/*!
 *  @abstract If YES, then this method will download any encryption keys in manifest.
 *            Normally, you would pass YES, but this allows for custom behaviors.
 */
@property (nonatomic, assign)Boolean includeEncryption;

/*!
*  @abstract For manifests containing multiple profiles, Virtuoso will select the highest bitrate
*            profile whose bitrate doesn't exceed this value. A value of 1 means "use the lowest
*            bitrate." If there's no profile of lower bitrate than maximumBitrate, Virtuoso will
*            select the lowest bitrate profile.  A value of INT_MAX means "use the highest bitrate."
 *           Defaults to maximum rate INT_MAX.
*/
@property (nonatomic, assign)long long maximumBitrate;

/*!
 * @abstract Same as maximumBitrate, but for the audio portion of the stream.  If the audio for
 *           this asset is contained within the video profile, this value is ignored.
 *           Defaults to maximum rate INT_MAX.
 */
@property (nonatomic, assign)long long maximumAudioBitrate;

/*!
 *  @abstract When this asset should become available
 *
 *  @discussion Virtuoso will download assets as soon as they are enqueued.
 *              But in some cases, you may wish to embargo an asset.
 *              You do so by setting the publishDate property in the future.
 *              Until this date, Virtuoso will disallow access to this asset via the
 *              VirtuosoClientHTTPServer, and will not include this asset in any filtered
 *              query methods.
 *
 *  @see expiryDate
 */
@property (nonatomic, copy)NSDate* _Nullable publishDate;

/*!
 *  @abstract As soon as possible after 'expiryDate' has passed, Virtuoso automatically deletes the asset.
 *
 *  @discussion A nil value means the asset never expires.
 */
@property (nonatomic, copy)NSDate* _Nullable expiryDate;

/*!
 *  @abstract After the asset has completed download, as soon as possible after 'expiryAfterDownload'
 *            time has elapsed, Virtuoso automatically deletes the asset.
 *
 *  @discussion A value of zero means the asset never expires.
 */
@property (nonatomic, assign)NSTimeInterval expiryAfterDownload;

/*!
 *  @abstract After the asset is first played, as soon as possible after 'expiryAfterPlay' time has elapsed,
 *            Virtuoso automatically deletes the asset.
 *
 *  @see firstPlayDateTime
 *
 *  @discussion A value of zero means the asset never expires.
 */
@property (nonatomic, assign)NSTimeInterval expiryAfterPlay;

/*!
 *  @abstract The asset-specific lifetime download limit.
 *
 *  @discussion The Backplane specifies a globally applied lifetime download limit for all assets.  An individual
 *              asset may not be downloaded more than this number of times in a given account.  Once the asset has
 *              been successfully downloaded this many time, future attempts to download the asset will return an error.
 *              This optional value may be specified to override the lifetime download limit for this particular asset.
 *              If this value is greater than 0, it will be used for permissions calculations instead of the backplane-
 *              defined value.  This value is provided during creation of the asset and cannot be changed after creation.
 */
@property (nonatomic, assign)NSInteger assetDownloadLimit;

/*!
 *  @abstract If this asset is ready to begin FastPlay playback
 *
 *  @discussion In order for an asset to successfully FastPlay, a small amount of the asset must be pre-downloaded.
 *              Until that initial download has completed, playing the asset will behave as if FastPlay was not
 *              enabled.
 */
@property (nonatomic, assign)Boolean enableFastPlay;

/*!
 *  @abstract If true the asset is automatically added to the download queue.
 */
@property (nonatomic, assign)Boolean autoAddToQueue;

/*!
 *  @abstract Optional array of ancillary files.
 */
@property (nonatomic, assign)NSArray<VirtuosoAncillaryFile*>* _Nullable ancillaries;

/*!
 *  @abstract AdsProvider assocated with the Asset.
 *
 */
@property (nonatomic, assign)VirtuosoAdsProvider* _Nullable adsProvider;

/*!
 *  @abstract The generic userInfo metadata for this asset
 *
 *  @discussion The userInfo dictionary is for you to store metadata alongside this asset.
 *              Since Virtuoso serializes this object, all objects contained within the userInfo dictionary
 *              MUST be property list compatible objects.  If you attempt to save non-compatible objects,
 *              the userInfo dictionary won't be persisted.
 */
@property (nonatomic, copy)NSDictionary* _Nullable userInfo;

/*!
 *  @abstract Creates instance
 *
 *  @discussion This constructor creates an instance with the basic properties needed by all Asset types.
 *
 *  @param url Where the manifest lives on the Internet.
 *
 *  @param assetID A unique identifier for the asset. Used in all log events.
 *
 *  @param description A description of the asset.  Virtuoso only uses this in log output.
 *
 *  @param type Type of asset to create. See kVDE_AssetType
 *
 *  @return A instance of this class, nil if an error was encountered.
 */
-(instancetype _Nullable)initWithURL:(NSString* _Nonnull)url assetID:(NSString* _Nonnull)assetID description:(NSString* _Nonnull)description type:(kVDE_AssetType)type;

@end

#endif /* VirtuosoAssetConfig_h */


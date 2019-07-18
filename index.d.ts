/**
 * Container for authorization information.
 */
export interface AuthInfo {
    /**
     * String containing the authentication protocol name, such as "MIT-MAGIC-COOKIE-1" or "XDM-AUTHORIZATION-1".
     */
    name: string;

    /**
     * Data interpreted in a protocol-specific manner.
     */
    data: string;
}

export interface Extension {
    name: string;
    globalId: number;
}

export interface GenericError {
	responseType: number;
	errorCode: number;

	/**
	 * Sequence number.
	 */
	sequence: number;

	/**
	 * Resource ID for requests with side effects only.
	 */
	resourceId: number;

	/**
	 * Minor opcode of the failed request.
	 */
	minorCode: number;

	/**
	 * Major opcode of the failed request.
	 */
	majorCode: number;
	fullSequence: number;
}

export interface GenericEvent {
	responseType: number;

	/**
	 * Sequence number
	 */
	sequence: number;

	fullSequence: number;
}

export interface QueryExtensionReply {
    responseType: number;
    sequence: number;
    length: number;
    present: number;
    majorOpcode: number;
    firstEvent: number;
    firstError: number;
}

export interface Setup {
    status: number;
    protocolMajorVersion: number;
    protocolMinorVersion: number;
    length: number;
    releaseNumber: number;
    resourceIdBase: number;
    resourceIdMask: number;
    motionBufferSize: number;
    vendorLength: number;
    maximumRequestLength: number;
    rootsLength: number;
    pixmapFormatsLength: number;
    imageByteOrder: number;
    bitmapFormatBitOrder: number;
    bitmapFormatScanlineUnit: number;
    minKeycode: number;
    maxKeycode: number;
}

export interface VoidCookie {
	sequence: number;
}

export enum ConnectionStatus {
    Ok = 0,
    Error = 1,
    ExtensionNotSupported = 2,
    MemoryInsufficient = 3,
    RequestLengthExceeded = 4,
    ParseError = 5,
    InvalidScreen = 6,
    FdPassingFailed = 7
}

/**
 * A class that contains all data and functions that XCB needs to communicate with an X server.
 */
export class Connection {
    /**
     * Connects to the X server.
     * @param displayName The name of the display.
     * @param screen Preferred screen number.
     */
    constructor(displayName: string, screen: number);

    /**
     * Connects to the X server, using an authorization information.
     * @param displayName The name of the display.
     * @param authInfo The authorization information.
     * @param screen Preferred screen number.
     */
    constructor(displayName: string, authInfo: AuthInfo, screen: number);

    /**
     * Connects to the X server.
     * @param fd The file descriptor.
     * @param authInfo Authentication data.
     */
    constructor(fd: number, authInfo: AuthInfo);

    /**
     * Discards the reply for a request.
     * @param sequence The request sequence number from a cookie.
     */
    discardReply(sequence: number): void;

    /**
     * Discards the reply for a request, given by a 64-bit sequence number.
     * @param sequence 64-bit sequence number as returned by `sendRequest64`
     */
    discardReply64(sequence: number): void;

    /**
     * Closes the connection.
     */
    disconnect(): void;

    /**
     * Forces any buffered output to be written to the server.
     * @throws An exception if this fails.
     */
    flush(): void;

    /**
     * Allocates an XID for a new object.
     * @returns A newly allocated XID.
     */
    generateId(): number;

    /**
     * Caches reply information from QueryExtension requests.
     * @param extension The extension data.
	 * @async Extension data may have to be fetched from the server beforehand.
     */
    getExtensionData(extension: Extension): Promise<QueryExtensionReply>;

    /**
     * Returns the maximum request length that this server accepts.
     * @returns The maximum request length field.
     */
    getMaximumRequestLength(): Promise<number>;

    /**
     * Access the data returned by the server upon connection.
     */
    getSetup(): Setup;

    /**
     * Test whether the connection has shut down due to a fatal error.
     */
	hasError(): ConnectionStatus;

	/**
	 * Parses a display string name in the form documented by X(7x).
	 * @param name The name of the display.
	 * @param host Hostname.
	 * @param display Display number.
	 * @param screen Screen number.
	 * @throws On failure.
	 */
	parseDisplay(name: string, host: string, display: number, screen: number): void;

	/**
	 * Returns the next event or error from the server.
	 * @returns The next event from the server.
	 * @throws If no event is available.
	 */
	pollForEvent(): GenericEvent;

	/**
	 * Returns the next event without reading from the connection.
	 * @returns The next already queued event from the server.
	 */
	pollForQueuedEvent(): GenericEvent;

	/**
	 * Prefetch of extension data into the extension cache.
	 * @param extension The extension data.
	 */
	prefetchExtensionData(extension: Extension): void;

	/**
	 * Prefetch the maximum request length without blocking.
	 */
	prefetchMaximumRequestLength(): void;

	/**
	 * Return the error for a request.
	 * @param cookie The request cookie.
	 * @throws If none can ever arrive.
	 */
	requestCheck(cookie: VoidCookie): GenericError;

	/**
	 * Returns the next event or error from the server.
	 * @returns The next event from the server.
	 * @throws In the event of an I/O error
	 * @async Blocks until either an event or error arrive, or an I/O error occurs.
	 */
	waitForEvent(): Promise<GenericEvent>;
}

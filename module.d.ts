// Original documentation obtained from XCB 1.12 API.

export enum Allow {
    /**
     * For AsyncPointer, if the pointer is frozen by the client, pointer event processing continues normally. If the pointer is frozen twice by the client on behalf of two separate grabs, AsyncPointer thaws for both. AsyncPointer has no effect if the pointer is not frozen by the client, but the pointer need not be grabbed by the client.
     */
    AsyncPointer,

    /**
     * For SyncPointer, if the pointer is frozen and actively grabbed by the client, pointer event processing continues normally until the next ButtonPress or ButtonRelease event is reported to the client, at which time the pointer again appears to freeze. However, if the reported event causes the pointer grab to be released, then the pointer does not freeze. SyncPointer has no effect if the pointer is not frozen by the client or if the pointer is not grabbed by the client.
     */
    SyncPointer,

    /**
     * For ReplayPointer, if the pointer is actively grabbed by the client and is frozen as the result of an event having been sent to the client (either from the activation of a GrabButton or from a previous AllowEvents with mode SyncPointer but not from a GrabPointer), then the pointer grab is released and that event is completely reprocessed, this time ignoring any passive grabs at or above (towards the root) the grab-window of the grab just released. The request has no effect if the pointer is not grabbed by the client or if the pointer is not frozen as the result of an event.
     */
    ReplayPointer,

    /**
     * For AsyncKeyboard, if the keyboard is frozen by the client, keyboard event processing continues normally. If the keyboard is frozen twice by the client on behalf of two separate grabs, AsyncKeyboard thaws for both. AsyncKeyboard has no effect if the keyboard is not frozen by the client, but the keyboard need not be grabbed by the client.
     */
    AsyncKeyboard,

    /**
     * For SyncKeyboard, if the keyboard is frozen and actively grabbed by the client, keyboard event processing continues normally until the next KeyPress or KeyRelease event is reported to the client, at which time the keyboard again appears to freeze. However, if the reported event causes the keyboard grab to be released, then the keyboard does not freeze. SyncKeyboard has no effect if the keyboard is not frozen by the client or if the keyboard is not grabbed by the client.
     */
    SyncKeyboard,

    /**
     * For ReplayKeyboard, if the keyboard is actively grabbed by the client and is frozen as the result of an event having been sent to the client (either from the activation of a GrabKey or from a previous AllowEvents with mode SyncKeyboard but not from a GrabKeyboard), then the keyboard grab is released and that event is completely reprocessed, this time ignoring any passive grabs at or above (towards the root) the grab-window of the grab just released. The request has no effect if the keyboard is not grabbed by the client or if the keyboard is not frozen as the result of an event.
     */
    ReplayKeyboard,

    /**
     * For AsyncBoth, if the pointer and the keyboard are frozen by the client, event processing for both devices continues normally. If a device is frozen twice by the client on behalf of two separate grabs, AsyncBoth thaws for both. AsyncBoth has no effect unless both pointer and keyboard are frozen by the client.
     */
    AsyncBoth,

    /**
     * For SyncBoth, if both pointer and keyboard are frozen by the client, event processing (for both devices) continues normally until the next ButtonPress, ButtonRelease, KeyPress, or KeyRelease event is reported to the client for a grabbed device (button event for the pointer, key event for the keyboard), at which time the devices again appear to freeze. However, if the reported event causes the grab to be released, then the devices do not freeze (but if the other device is still grabbed, then a subsequent event for it will still cause both devices to freeze). SyncBoth has no effect unless both pointer and keyboard are frozen by the client. If the pointer or keyboard is frozen twice by the client on behalf of two separate grabs, SyncBoth thaws for both (but a subsequent freeze for SyncBoth will only freeze each device once).
     */
    SyncBoth
}

/**
 * A structure that contains all data that XCB needs to communicate with an X server. This is also a wrapper class for all XCB functions that accept `xcb_connection_t` as the first argument.
 */
export class Connection {
    /**
     * Releases queued events if the client has caused a device (pointer/keyboard) to freeze due to grabbing it actively. This request has no effect if `time` is earlier than the last-grab time of the most recent active grab for this client or if `time` is later than the current X server time.
     * @param mode A bitmask of `Allow` values.
     * @param time Timestamp to avoid race conditions when running X over the network. 
     */
    allowEvents(mode: Allow, time: number): VoidCookie;
}

/**
 * A generic cookie structure.
 */
export interface VoidCookie {
    sequence: number;
}
const XCB = require('bindings')('xcb');

describe('Core API', () => {
	describe('Connection', () => {
        const connection = new XCB.Connection();

        test('connect', () => {
            expect(() => connection.connect('lol', 0)).toThrowError();
            expect(() => connection.connect()).not.toThrowError();
        });

        test('flush', () => {
            expect(connection.flush()).toBeGreaterThan(0);
        });

        test('generateId', () => {
            expect(connection.generateId()).toBeGreaterThan(0);
        });

        test('getFileDescriptor', () => {
            expect(connection.getFileDescriptor()).toBeGreaterThan(-1);
        });

        test('pollForEvent', () => {
            expect(connection.pollForEvent()).toBeNull();
        });

        test('pollForReply', () => {
            expect(() => connection.pollForReply()).toThrow();
            expect(connection.pollForReply(0)).toBeUndefined();
        });

        test('disconnect', () => {
            expect(connection.disconnect()).toBeUndefined();
        });
    });
});

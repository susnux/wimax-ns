/*
 * Event loop
 * Copyright (c) 2002-2005, Jouni Malinen <jkmaline@cc.hut.fi>
 * All Rights Reserved.
 *
 * This file defines an event loop interface that supports processing events
 * from registered timeouts (i.e., do something after N seconds), sockets
 * (e.g., a new packet available for reading), and signals. eloop.c is an
 * implementation of this interface using select() and sockets. This is
 * suitable for most UNIX/POSIX systems. When porting to other operating
 * systems, it may be necessary to replace that implementation with OS specific
 * mechanisms.
 */

#ifndef ELOOP_H
#define ELOOP_H

/* Magic number for eloop_cancel_timeout() */
#define ELOOP_ALL_CTX (void *) -1

/**
 * eloop_init() - Initialize global event loop data
 * @user_data: Pointer to global data passed as eloop_ctx to signal handlers
 * Returns: 0 on success, -1 on failure
 *
 * This function must be called before any other eloop_* function. user_data
 * can be used to configure a global (to the process) pointer that will be
 * passed as eloop_ctx parameter to signal handlers.
 */
int eloop_init(void *user_data);

/**
 * eloop_register_read_sock - Register handler for read events
 * @sock: File descriptor number for the socket
 * @handler: Callback function to be called when data is available for reading
 * @eloop_data: Callback context data (eloop_ctx)
 * @user_data: Callback context data (sock_ctx)
 * Returns: 0 on success, -1 on failure
 *
 * Register a read socket notifier for the given file descriptor. The handler
 * function will be called whenever data is available for reading from the
 * socket.
 */
int eloop_register_read_sock(int sock,
			     void (*handler)(int sock, void *eloop_ctx,
					     void *sock_ctx),
			     void *eloop_data, void *user_data);

/**
 * eloop_unregister_read_sock - Unregister handler for read events
 * @sock: File descriptor number for the socket
 *
 * Unregister a read socket notifier that was previously registered with
 * eloop_register_read_sock().
 */
void eloop_unregister_read_sock(int sock);

/**
 * eloop_register_event - Register handler for generic events
 * @event: Event to wait (eloop implementation specific)
 * @event_size: Size of event data
 * @handler: Callback function to be called when event is triggered
 * @eloop_data: Callback context data (eloop_data)
 * @user_data: Callback context data (user_data)
 * Returns: 0 on success, -1 on failure
 *
 * Register an event handler for the given event. The handler function will be
 * called whenever the event is triggered.
 */
int eloop_register_event(void *event, size_t event_size,
			 void (*handler)(void *eloop_data, void *user_ctx),
			 void *eloop_data, void *user_data);

/**
 * eloop_unregister_event - Unregister handler for a generic event
 * @event: Event to cancel (eloop implementation specific)
 * @event_size: Size of event data
 *
 * Unregister a generic event notifier that was previously registered with
 * eloop_register_event().
 */
void eloop_unregister_event(void *event, size_t event_size);

/**
 * eloop_register_timeout - Register timeout
 * @secs: Number of seconds to the timeout
 * @usecs: Number of microseconds to the timeout
 * @handler: Callback function to be called when timeout occurs
 * @eloop_data: Callback context data (eloop_ctx)
 * @user_data: Callback context data (sock_ctx)
 * Returns: 0 on success, -1 on failure
 *
 * Register a timeout that will cause the handler function to be called after
 * given time.
 */
int eloop_register_timeout(unsigned int secs, unsigned int usecs,
			   void (*handler)(void *eloop_ctx, void *timeout_ctx),
			   void *eloop_data, void *user_data);

/**
 * eloop_cancel_timeout - Cancel timeouts
 * @handler: Matching callback function
 * @eloop_data: Matching eloop_data or %ELOOP_ALL_CTX to match all
 * @user_data: Matching user_data or %ELOOP_ALL_CTX to match all
 * Returns: Number of cancelled timeouts
 *
 * Cancel matching <handler,eloop_data,user_data> timeouts registered with
 * eloop_register_timeout(). ELOOP_ALL_CTX can be used as a wildcard for
 * cancelling all timeouts regardless of eloop_data/user_data.
 */
int eloop_cancel_timeout(void (*handler)(void *eloop_ctx, void *sock_ctx),
			 void *eloop_data, void *user_data);

/**
 * eloop_register_signal - Register handler for signals
 * @sig: Signal number (e.g., SIGHUP)
 * @handler: Callback function to be called when the signal is received
 * @user_data: Callback context data (signal_ctx)
 * Returns: 0 on success, -1 on failure
 *
 * Register a callback function that will be called when a signal is received.
 * The callback function is actually called only after the system signal
 * handler has returned. This means that the normal limits for sighandlers
 * (i.e., only "safe functions" allowed) do not apply for the registered
 * callback.
 *
 * Signals are 'global' events and there is no local eloop_data pointer like
 * with other handlers. The global user_data pointer registered with
 * eloop_init() will be used as eloop_ctx for signal handlers.
 */
int eloop_register_signal(int sig,
			  void (*handler)(int sig, void *eloop_ctx,
					  void *signal_ctx),
			  void *user_data);

/**
 * eloop_register_signal_terminate - Register handler for terminate signals
 * @handler: Callback function to be called when the signal is received
 * @user_data: Callback context data (signal_ctx)
 * Returns: 0 on success, -1 on failure
 *
 * Register a callback function that will be called when a process termination
 * signal is received. The callback function is actually called only after the
 * system signal handler has returned. This means that the normal limits for
 * sighandlers (i.e., only "safe functions" allowed) do not apply for the
 * registered callback.
 *
 * Signals are 'global' events and there is no local eloop_data pointer like
 * with other handlers. The global user_data pointer registered with
 * eloop_init() will be used as eloop_ctx for signal handlers.
 *
 * This function is a more portable version of eloop_register_signal() since
 * the knowledge of exact details of the signals is hidden in eloop
 * implementation. In case of operating systems using signal(), this function
 * registers handlers for SIGINT and SIGTERM.
 */
int eloop_register_signal_terminate(void (*handler)(int sig, void *eloop_ctx,
						    void *signal_ctx),
				    void *user_data);

/**
 * eloop_register_signal_reconfig - Register handler for reconfig signals
 * @handler: Callback function to be called when the signal is received
 * @user_data: Callback context data (signal_ctx)
 * Returns: 0 on success, -1 on failure
 *
 * Register a callback function that will be called when a reconfiguration /
 * hangup signal is received. The callback function is actually called only
 * after the system signal handler has returned. This means that the normal
 * limits for sighandlers (i.e., only "safe functions" allowed) do not apply
 * for the registered callback.
 *
 * Signals are 'global' events and there is no local eloop_data pointer like
 * with other handlers. The global user_data pointer registered with
 * eloop_init() will be used as eloop_ctx for signal handlers.
 *
 * This function is a more portable version of eloop_register_signal() since
 * the knowledge of exact details of the signals is hidden in eloop
 * implementation. In case of operating systems using signal(), this function
 * registers a handler for SIGHUP.
 */
int eloop_register_signal_reconfig(void (*handler)(int sig, void *eloop_ctx,
						   void *signal_ctx),
				   void *user_data);

/**
 * eloop_run - Start the event loop
 *
 * Start the event loop and continue running as long as there are any
 * registered event handlers. This function is run after event loop has been
 * initialized with event_init() and one or more events have been registered.
 */
void eloop_run(void);

/**
 * eloop_terminate - Terminate event loop
 *
 * Terminate event loop even if there are registered events. This can be used
 * to request the program to be terminated cleanly.
 */
void eloop_terminate(void);

/**
 * eloop_destroy - Free any resources allocated for the event loop
 *
 * After calling eloop_destoy(), other eloop_* functions must not be called
 * before re-running eloop_init().
 */
void eloop_destroy(void);

/**
 * eloop_terminated - Check whether event loop has been terminated
 * Returns: 1 = event loop terminate, 0 = event loop still running
 *
 * This function can be used to check whether eloop_terminate() has been called
 * to request termination of the event loop. This is normally used to abort
 * operations that may still be queued to be run when eloop_terminate() was
 * called.
 */
int eloop_terminated(void);

/**
 * eloop_wait_for_read_sock - Wait for a single reader
 * @sock: File descriptor number for the socket
 *
 * Do a blocking wait for a single read socket.
 */
void eloop_wait_for_read_sock(int sock);

#endif /* ELOOP_H */

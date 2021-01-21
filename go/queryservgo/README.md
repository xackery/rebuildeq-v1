queryservgo was an experiment to see if we could move queryserv to a go-based service.
This should be considered DEPRECATED and likely removed in the future all together.
The ideal solution to queryserv's replacement is to use NATS to broadcast the events to a go program to do the SQL commands in a buffer not burdening eqemu's binaries.
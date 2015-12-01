Find the name of the weekday of a certain date
==============================================

For example:
	wd 2015-12-01 # '>' means output
	> 2015-12-1:Tuesday

The date has to have the format YEAR-MONTH-DAY,
somewhat similar to ISO 8601.
Unlike ISO 8601 this allows years bigger than 5 digits.
wd(1) does not allow negative years or the year 0.

For more information, consult your local manpage.

Installation is done by typing
	make install
into your 'command line' or 'terminal' (read these quotes sarcastically).
I assume you have got a c89 compiler and some version of make installed.

This is licensed under the MIT/X11 license.

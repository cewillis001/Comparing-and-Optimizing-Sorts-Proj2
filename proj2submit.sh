#!/bin/tcsh

# Start submission settings.

setenv COURSE cop4531p
setenv ASSIGNMENT project2
setenv FILES "gsort.h report.txt"

# End submission settings.

setenv FAILED1 0
setenv FAILED2 0
setenv FAILED3 0

#echo "Archiving..."

if (-e Makefile) mv Makefile makefile
tar -cvf $ASSIGNMENT.tar $FILES >& /dev/null

if ($? != 0) then

    set FAILED1=1

endif

#echo "Sending email..."

gzip $ASSIGNMENT.tar
uuencode $ASSIGNMENT.tar.gz < $ASSIGNMENT.tar.gz > $ASSIGNMENT
elm -s "$ASSIGNMENT submission" $COURSE < $ASSIGNMENT >& /dev/null

if ($? != 0) then

    set FAILED2=1

endif

#echo "Cleaning up..."

rm -f ./$ASSIGNMENT
rm -f ./$ASSIGNMENT.tar.gz

if ("$ASSIGNMENT" == "assign0") then
    
    grep -m 1 -i 'fsu username:' info.txt >& /dev/null
    
    if ($? != 0) then 
    
        set FAILED3=1

    endif

endif

if ($FAILED1 == 1) then

    echo "\e[1;31m\n*** SUBMISSION IS INCOMPLETE ***.\n\nFailed to locate all required files for submission.  Make sure you have them in the same directory as this script.\n\e[0m"

endif

if ($FAILED2 == 1) then

    echo "\e[1;31m\n*** SUBMISSION NOT SENT ***.\n\nFailed to email submission.  Make sure you are using the shell server (type \e[1;34mssh shell\e[1;31m).\n\e[0m"

endif

if ($FAILED3 == 1 && $FAILED1 == 0) then
    
    echo "\e[1;31m\n*** SUBMISSION IS INVALID ***.\n\nYour info.txt doesn't contain the heading \e[1;34mFSU Username: \e[1;31mbefore your FSU username.  Make sure to include this before submitting.\n\e[0m"

endif

if ($FAILED1 == 0 && $FAILED2 == 0 && $FAILED3 == 0) then

    echo "\e[1;34m\n*** SUBMISSION SENT SUCCESSFULLY ***.\n\nMake sure you receive two email responses (as mentioned in the course organizer).  Note that these will come to your CS email, not your FSU email.\n\e[0m"

endif

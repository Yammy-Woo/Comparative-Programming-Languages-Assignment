#!/usr/bin/env zsh
#
# The TASK environment variable will be set automatically in the Einstein execution
# environment.
#
# For testing, try to set the TASK environment variable...
#
[[ -z $TASK ]] && [[ -f $PWD:t ]] && TASK=$PWD:t
[[ -z $TASK ]] && [[ -f $PWD:h:t ]] && TASK=$PWD:h:t

# Fail (exit) immediately if any of the following commands fail.
#
set -e

# Compile user's Java code
javac $TASK

# The show-exec-command is available in the Einstein execution environment.
# It is also available in the `bin` directory in the project repo.  You can
# install it locally from there for testing.
#
file =  ('' '__tests/empty.txt' '__tests/one-input.txt' '__tests/test.txt' '__tests/numbers.txt')
for v in "$file[@]"
do
  show-exec-command java ${TASK%.java} $v
done

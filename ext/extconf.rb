require 'mkmf'

$CFLAGS << ' -Ditex2MML_CAPTURE -fPIC'
create_makefile("itex2MML")

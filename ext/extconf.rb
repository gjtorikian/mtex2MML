require 'mkmf'

$CFLAGS << ' -Dmtex2MML_CAPTURE'
create_makefile('mtex2MML')

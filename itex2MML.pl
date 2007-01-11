# itex2MML
# version 0.12
# copyright 2003-2005, Jacques Distler
#

use MT;
use File::Temp qw(tempfile);

MT->add_text_filter(itexToMML => {
	label => 'itex to MathML',
	on_format => sub { &itexToMML; },
});
MT->add_text_filter(itexToMMLpara => {
        label => 'itex to MathML with parbreaks',
        on_format => sub { &itexToMMLpara; },
});

sub itexToMML {
    $_=shift;
    $_=~ s/\r//g;
    my ($Reader,$outfile) = tempfile( UNLINK => 1 );
    my ($Writer,$infile) = tempfile( UNLINK => 1 );
    print $Writer "$_";
    system("/usr/local/bin/itex2MML <$infile >$outfile");
    my @out = <$Reader>;
    close $Reader;
    close $Writer;
    eval {unlink ($infile, $outfile);};
    join('',@out);
}

sub itexToMMLpara {
    $_=shift;
    $_=~ s/\r//g;
    $_=splitparas($_);
    my ($Reader,$outfile) = tempfile( UNLINK => 1 );
    my ($Writer,$infile) = tempfile( UNLINK => 1 );
    print $Writer "$_";
    system("/usr/local/bin/itex2MML <$infile >$outfile");
    my @out = <$Reader>;
    close $Reader;
    close $Writer;
    eval {unlink ($infile, $outfile);};
    join('',@out);
}

sub splitparas {
    my $str = shift;
    $str ||= '';
    my @paras = split /\n\n/, $str;
    for my $p (@paras) {
        if ($p !~ m@^</?(?:h1|h2|h3|h4|h5|h6|table|ol|dl|ul|menu|dir|p|pre|center|form|fieldset|select|blockquote|address|div|hr)@) {
            $p = "<p>$p</p>";
        }
    }
    join "\n\n", @paras;
}

1;

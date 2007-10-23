# itex2MML
# version 1.1
# copyright 2003-2007, Jacques Distler
#

package MT::Plugin::itex2MML;

use MT;
use File::Temp qw(tempfile);

use vars qw( $VERSION );
$VERSION = '1.1';

eval{ require MT::Plugin;};
unless ($@) {
   my $plugin = {
      name => "itex2MML",
      version => $VERSION,
      description => "A Text-Filter, translating embedded itex equations into MathML",
      doc_link => 'http://golem.ph.utexas.edu/~distler/blog/itex2MML.html',
   };
   MT->add_plugin(new MT::Plugin($plugin));
}

MT->add_text_filter(itexToMML => {
	label => 'itex to MathML',
	on_format => sub { &itexToMML; },
});
MT->add_text_filter(itexToMMLpara => {
        label => 'itex to MathML with parbreaks',
        on_format => sub { &itexToMMLpara; },
});

my $itex2mml_number_equations = 1;
my $itex2mml_binary = "/usr/local/bin/itex2MML --raw-filter";

sub itexToMML {
    $_=shift;
    $ctx = shift;
    $_=~ s/\r//g;
    $_ = number_equations($_, $itex2mml_number_equations, $ctx);
    my ($Reader,$outfile) = tempfile( UNLINK => 1 );
    my ($Writer,$infile) = tempfile( UNLINK => 1 );
    print $Writer "$_";
    system("$itex2mml_binary <$infile >$outfile");
    my @out = <$Reader>;
    close $Reader;
    close $Writer;
    eval {unlink ($infile, $outfile);};
    join('',@out);
}

sub itexToMMLpara {
    $_ = shift;
    $ctx = shift;
    $_=~ s/\r//g;
    $_ = number_equations($_, $itex2mml_number_equations, $ctx);
    $_ = splitparas($_);
    my ($Reader,$outfile) = tempfile( UNLINK => 1 );
    my ($Writer,$infile) = tempfile( UNLINK => 1 );
    print $Writer "$_";
    system("$itex2mml_binary <$infile >$outfile");
    my @out = <$Reader>;
    close $Reader;
    close $Writer;
    eval {unlink ($infile, $outfile);};
    join('',@out);
}

sub splitparas {
    my $str = shift;
    $str ||= '';
    my @paras = split /\n{2,}/, $str;
    for my $p (@paras) {
        if ($p !~ m@^</?(?:h1|h2|h3|h4|h5|h6|table|ol|dl|ul|menu|dir|p|pre|center|form|fieldset|select|blockquote|address|div|hr)@) {
            $p = "<p>$p</p>";
        }
    }
    join "\n\n", @paras;
}

sub number_equations {
  $_ = shift;
  my $arg_value = shift;
  my $ctx = shift;

  if ($arg_value == 0) {return $_;}
  
  my $prefix = "eq";
  if ((defined $ctx)  && (ref($ctx) eq 'MT::Template::Context')) {
    if ($ctx->stash('comment') ) {
       $prefix = "c" . $ctx->stash('comment')->id;
    } elsif ($ctx->stash('entry') ) {
       $prefix = "e" . $ctx->stash('entry')->id;
    }
  }
  my $cls = "numberedEq";

  my %eqnumber;
  my $eqno=1;

  # add equation numbers to \[...\]
  #  - introduce a wrapper-<div> and a <span> with the equation number
  while (s/\\\[(.*?)\\\]/\n\n<div class=\"$cls\"><span>\($eqno\)<\/span>\$\$$1\$\$<\/div>\n\n/s) {
    $eqno++;
  }

  # assemble equation labels into a hash
  # - remove the \label{} command, collapse surrounding whitespace
  # - add an ID to the wrapper-<div>. prefix it to give a fighting chance
  #   for the ID to be unique
  # - hash key is the equation label, value is the equation number
  while (s/<div class=\"$cls\"><span>\((\d+)\)<\/span>\$\$((?:[^\$]|\\\$)*)\s*\\label{(\w*)}\s*((?:[^\$]|\\\$)*)\$\$<\/div>/<div class=\"$cls\" id=\"$prefix:$3\"><span>\($1\)<\/span>\$\$$2$4\$\$<\/div>/s) {
    $eqnumber{"$3"} = $1;
  }

  # add cross-references
  # - they can be either (eq:foo) or \eqref{foo}
  s/\(eq:(\w+)\)/\(<a href=\"#$prefix:$1\">$eqnumber{"$1"}<\/a>\)/g;
  s/\\eqref\{(\w+)\}/\(<a href=\'#$prefix:$1\'>$eqnumber{"$1"}<\/a>\)/g;
  
  return $_;
}

1;

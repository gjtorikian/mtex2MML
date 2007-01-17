# TextileMarkdownMML.pl
#
# Provides two MT text filters
#
#   Textile+itex2MML
#  Markdown+itex2MML
#
# You must have the itex2MML, Textile 1.1 and Markdown filters already installed
# This filter first runs your text through itex2MML and then through
# either Textile or Markdown.
#
# The Textile+itex2MML filter requires a small patch to the Textile 1.1 plugin.
# See:
#     http://golem.ph.utexas.edu/~distler/blog/archives/000374.html
#
# Based on textileMML.pl, by Yuan-Chung Cheng.
#
# Copyright, 2004-2007, Jacques Distler.
# This code is released under the GPL
#

package MT::Plugins::TextileMarkdownMML;

use vars qw($VERSION);
$VERSION = 1.2;

use strict;

use MT;
use MT::Template::Context;

eval{ require MT::Plugin;};
unless ($@) {
   my $plugin = {
      name => "TextileMarkdownMML",
      version => $VERSION,
      description => "A Text-Filter, adding support for embedded itex equations to Markdown and/or Textile 1.1. Requires itex2MML and one or both of the latter plugins be installed.",
      doc_link => 'http://golem.ph.utexas.edu/~distler/blog/archives/000374.html',
   };
   MT->add_plugin(new MT::Plugin($plugin));
}

my $filters = MT->all_text_filters();

if (exists($filters->{'textile_1'}) && exists($filters->{'itexToMML'})) {
	MT->add_text_filter('textile_1MML' => {
				     label => 'Textile with itex to MathML',
				     on_format => sub { &textileMML; },
				    });
}
if (exists($filters->{'markdown'}) && exists($filters->{'itexToMML'})) {
	MT->add_text_filter('markdownMML' => {
				     label => 'Markdown with itex to MathML',
				     on_format => sub { &markdownMML; },
				    });
}

sub textileMML {

  my $text=shift;
  my $ctx=shift;

  # now call apply_text_filters() to do the job
  $text=MT->apply_text_filters($text, ['itexToMML'], $ctx);
  $text=MT->apply_text_filters($text, ['textile_1'], $ctx);

  $text;
}

sub markdownMML {

  my $text=shift;
  my $ctx=shift;

  # now call apply_text_filters() to do the job
  $text=MT->apply_text_filters($text, ['itexToMML'], $ctx);
  $text=MT->apply_text_filters($text, ['markdown'], $ctx);

  $text;
}
1;


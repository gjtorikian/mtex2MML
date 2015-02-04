require 'test_helper'

MATHJAX_TEST_TEST_DIR = File.join('test', 'fixtures', 'MathJax')
MATHJAX_TEST_TEX_DIR = File.join(MATHJAX_TEST_TEST_DIR, 'LaTeXToMathML-tex')
MATHJAX_TEST_OUT_DIR = File.join(MATHJAX_TEST_TEST_DIR, 'LaTeXToMathML-out')
# stuff we just plain won't do
IGNORED_DIRS = %r(macro|mhchem)

def filter_array(array)
  array.select { |a| IGNORED_DIRS !~ a }
end

class MTex2MMLMathJaxTest < MiniTest::Test
  def setup
    @mtex = Mtex2MML::Parser.new
  end

  done_count = Dir['test/fixtures/MathJax/LaTeXToMathML-tex/**/*.tex'].length
  skipped_files = filter_array Dir['test/fixtures/MathJax/LaTeXToMathML-tex/**/*.xtex']
  incomplete_files = filter_array Dir['test/fixtures/MathJax/LaTeXToMathML-tex/**/*.no_tex']

  Dir['test/fixtures/MathJax/LaTeXToMathML-tex/**/*.tex'].each do |tex|
    define_method "test_#{tex}" do
      tex_contents = File.read(tex)
      outfile = tex.sub(MATHJAX_TEST_TEX_DIR + File::SEPARATOR, '').sub('.tex', '-ref.html')
      outfile = File.join(MATHJAX_TEST_OUT_DIR, outfile)
      expected = File.read(outfile)
      actual = @mtex.filter(tex_contents)

      write_to_test_file(actual)
      assert_equal(actual.strip, expected.strip)
    end
  end

  skipped_count = skipped_files.count
  incomplete_file_count = incomplete_files.count
  if skipped_count > 0
    total = (done_count + skipped_count).to_f
    coverage = done_count.fdiv(total) * 100
    skipped_files = skipped_files.join("\n * ")
    incomplete_files = incomplete_files.join("\n * ")
    puts "\n\nNot doing the following #{incomplete_file_count} MathJax tests:\n\n * #{incomplete_files}"
    puts "\n\nSkipping the following MathJax tests:\n\n * #{skipped_files}"
    puts "\n\n*** You did #{done_count} and skipped #{skipped_count}: #{coverage.round(2)}% coverage ***\n\n"
  end
end

require 'test_helper'

class MTex2MMLMathJaxTest < MiniTest::Test
  def setup
    @mtex = Mtex2MML::Parser.new
  end

  MATHJAX_TEST_TEST_DIR = File.join('test', 'fixtures', 'MathJax')
  MATHJAX_TEST_TEX_DIR = File.join(MATHJAX_TEST_TEST_DIR, 'LaTeXToMathML-tex')
  MATHJAX_TEST_OUT_DIR = File.join(MATHJAX_TEST_TEST_DIR, 'LaTeXToMathML-out')

  done_count = Dir['test/fixtures/MathJax/LaTeXToMathML-tex/**/*.tex'].length
  skipped_files = Dir['test/fixtures/MathJax/LaTeXToMathML-tex/**/*.{no_tex,xtex}']

  Dir['test/fixtures/MathJax/LaTeXToMathML-tex/**/alignat-1a.tex'].each do |tex|
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
  if skipped_count > 0
    total = (done_count + skipped_count).to_f
    coverage = done_count.fdiv(total) * 100
    skipped_files = skipped_files.join("\n * ")
    puts "\n\nSkipping the following MathJax tests:\n\n * #{skipped_files}"
    puts "\n\n*** You did #{done_count} and skipped #{skipped_count}: #{coverage.round(2)}% coverage ***\n\n"
  end
end

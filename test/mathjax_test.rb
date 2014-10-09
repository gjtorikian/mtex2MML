require 'test_helper'

class MTex2MMLMathJaxTest < MiniTest::Test

  def setup
    @mtex = Mtex2MML::Parser.new
  end

  MATHJAX_TEST_TEST_DIR = File.join('test', 'fixtures', 'MathJax')
  MATHJAX_TEST_TEX_DIR = File.join(MATHJAX_TEST_TEST_DIR, 'LaTeXToMathML-tex')
  MATHJAX_TEST_OUT_DIR = File.join(MATHJAX_TEST_TEST_DIR, 'LaTeXToMathML-out')

  DIRS_WE_DO = %w(above-below arrows)
  DIRS_WE_DO_GLOB = "{#{DIRS_WE_DO.join(',')}}"
  DIRS_IGNORED = %w(action AMScd)

  done_count = Dir["test/fixtures/MathJax/LaTeXToMathML-tex/#{DIRS_WE_DO_GLOB}/*.tex"].length
  skipped_count = Dir["test/fixtures/MathJax/LaTeXToMathML-tex/#{DIRS_WE_DO_GLOB}/*.xtex"].length

  Dir['test/fixtures/MathJax/LaTeXToMathML-tex/**/*.tex'].each do |tex|
    next unless tex =~ /#{DIRS_WE_DO.join("|")}/
    next if File.directory? tex

    define_method "test_#{tex}" do
      tex_contents = File.read(tex)
      outfile = tex.sub(MATHJAX_TEST_TEX_DIR + File::SEPARATOR, '').sub('.tex', '-ref.html')
      outfile = File.join(MATHJAX_TEST_OUT_DIR, outfile)
      expected = File.read(outfile)
      actual = @mtex.filter(tex_contents)

      write_to_test_file(actual) if tex =~ /Newextarrow/
      assert_equal(actual.strip, expected.strip)
      done_count += 1
    end
  end

  total = (done_count + skipped_count).to_f
  coverage = done_count.fdiv(total) * 100
  puts "\n\n*** You did #{done_count} and skipped #{skipped_count}: #{coverage.round(2)}% coverage ***\n\n"
end

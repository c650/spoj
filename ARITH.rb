#!/usr/bin/env ruby
n = gets.chomp.to_i

inputs = []
n.times{|x| inputs << gets.chomp}

inputs.each do |str|
	exp = str.split(/\*|\+|\-/)
	lhs = exp.first.to_i
	rhs = exp.last.to_i
	op = str[str =~ /\*|\+|\-/]

	l_len = lhs.to_s.length
	r_len = rhs.to_s.length


	case op
	when "+"
		len = [(lhs+rhs).to_s.length, lhs.to_s.length, rhs.to_s.length+1].max
		puts " "*(len-l_len).abs + lhs.to_s
		puts " "*(len-r_len-1).abs + op + rhs.to_s

		# calc dashes
		t = [r_len+1, (lhs+rhs).to_s.length].max
		puts " "*(len-t) + "-"*t

		puts format("%#{len}i", lhs+rhs)
	when "-"
		len = [(lhs-rhs).to_s.length, lhs.to_s.length, rhs.to_s.length+1].max
		puts " "*(len-l_len).abs + lhs.to_s
		puts " "*(len-r_len-1).abs + op + rhs.to_s

		# calc dashes
		t = [r_len+1, (lhs-rhs).to_s.length].max
		puts " "*(len-t) + "-"*t

		puts format("%#{len}i", lhs-rhs)
	when "*"
		top_len = [lhs.to_s.length, rhs.to_s.length+1].max
		len = [(lhs*rhs).to_s.length, top_len].max
		puts " "*(len-l_len).abs + lhs.to_s
		puts " "*(len-r_len-1).abs + op + rhs.to_s

		# calculate dashes
		t = [r_len+1, ((rhs % 10) * lhs).to_s.length].max
		puts " "*(len-t) + "-"*t

		rhs.to_s.reverse.split("").each_with_index do |num,i|
			partial_prod = (num.to_i * lhs).to_s
			puts " "*(len-partial_prod.length-i) + partial_prod
		end

		if rhs >= 10
			puts " "*(len-(lhs*rhs).to_s.length) + "-"*(lhs*rhs).to_s.length
			puts " "*(len-(lhs*rhs).to_s.length) + (lhs*rhs).to_s
		end
	end

	puts ""

end

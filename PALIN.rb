#!/usr/bin/env ruby

# not yet working
class String
	def is_pal
		front = 0
		back = self.length-1
		while front != back
			return false if self[front] != self[back]
			front += 1
			back -= 1
		end
		return true
	end

	def make_pal
		l = self.length/2 + (self.length % 2 == 0 ? -1 : 0)
		r = self.length/2

		self[l] = self[r] = (self[l].ord + (self[l].ord < self[r].ord ? 1 : 0)).chr
		l-=1;r+=1
		until l < 0 || r >= self.length
			if self[l] == self[r]
				l -=1
				r += 1
				next
			end

			lord = self[l].ord
			rord = self[r].ord
			self[l] = self[r] = [lord,rord].max.chr

			l -= 1
			r += 1
		end
	end
end

n = gets.chomp.to_i

n.times do |x|
	str = gets.chomp
	if str.is_pal
		str[str.length/2 - 1] = (str[str.length/2 - 1].ord + 1).chr if str.length % 2 == 0
		str[str.length/2] = (str[str.length/2].ord + 1).chr
	else
		str.make_pal
	end
	puts str
end

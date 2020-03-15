local key_codes = require('scripts/shared/key_codes')

keys = {}
keys.registered = {
	key_codes.VK_F6,
	key_codes.VK_F7
}

--refactor
keys.size = table.getn(keys.registered)

function handleKey (key)
	if key == key_codes.VK_F6 then
		playSound('sounds/money.wav')
	elseif key == key_codes.VK_F7 then
		playSound('sounds/off.wav')
	else
		print ('unknown key')
	end
end

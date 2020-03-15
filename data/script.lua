local key_codes = require('key_codes')

keys = {}
keys.registered = {
	key_codes.VK_F6,
	key_codes.VK_F7
}
keys.size = table.getn(keys.registered)

function handleKey (key)
	if key == key_codes.VK_F6 then
		writeMemory('health')
	elseif key == key_codes.VK_F7 then
		writeMemory('ammo')
	else
		print ('unknown key')
	end
end

local key_codes = require('scripts/shared/key_codes')

processName = 'KillingFloor.exe'
maxHealth = 100
registeredKeys = {
    key_codes.VK_F6,
    key_codes.VK_F7
}

function handleKey (key)
	if key == key_codes.VK_F6 then
		print('many many')
		playSound('sounds/money.wav')
	elseif key == key_codes.VK_F7 then
		print('off')
		playSound('sounds/off.wav')
	else
		print('unknown key')
	end
end

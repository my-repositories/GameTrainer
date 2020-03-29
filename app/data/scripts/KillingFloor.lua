local keyCodes = require('scripts/shared/key-codes')

cheatTableName = 'KillingFloor.CT'
processName = 'KillingFloor.exe'
maxHealth = 100

registeredKeys = {
    keyCodes.VK_F6,
    keyCodes.VK_F7
}

function handleKey (key)
	if key == keyCodes.VK_F6 then
		print('many many')
		playSound('sounds/money.wav')
	elseif key == keyCodes.VK_F7 then
		print('off')
		playSound('sounds/off.wav')
	end
end

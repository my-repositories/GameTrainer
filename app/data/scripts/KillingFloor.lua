local keyCodes = require('scripts/shared/key-codes')

cheatTableName = 'KillingFloor.CT'
processName = 'KillingFloor.exe'
maxHealth = 100

registeredKeys = {
    keyCodes.VK_F6,
    keyCodes.VK_F7,
    keyCodes.VK_F8,
    keyCodes.VK_F9
}

function handleKey (key, shift, ctrl, alt)
	if key == keyCodes.VK_F6 then
		print('god mode')
		playSound('sounds/on.wav')
	elseif key == keyCodes.VK_F7 then
		print('no reload')
        playSound('sounds/on.wav')
    elseif key == keyCodes.VK_F8 then
        print('increase money')
        playSound('sounds/money.wav')
    elseif key == keyCodes.VK_F9 and shift and ctrl and alt then
        print('level up for all perks')
        playSound('sounds/experience.wav')
	end
end

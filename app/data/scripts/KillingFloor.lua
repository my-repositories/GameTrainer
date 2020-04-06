local keyCodes = require('scripts/shared/key-codes')
local api = require('scripts/shared/api')

processName = 'KillingFloor.exe'
entries = readFile('KillingFloor.CT')

registeredKeys = {
    keyCodes.VK_F6,
    keyCodes.VK_F7,
    keyCodes.VK_F8,
    keyCodes.VK_F9
}

function handleKey (key, shift, ctrl, alt)
    if key == keyCodes.VK_F6 then
        print('god mode')
        api.playSound('sounds/on.wav')
    elseif key == keyCodes.VK_F7 then
        print('no reload')
        api.playSound('sounds/on.wav')
    elseif key == keyCodes.VK_F8 then
        api.addValueTo(entries.money, 1000)
        print('increase money')
        api.playSound('sounds/money.wav')
    elseif key == keyCodes.VK_F9 and shift and ctrl and alt then
        print('level up for all perks')
        api.playSound('sounds/experience.wav')
    end
end

function tick()
    -- addValueTo(entries.armor, 100)
end

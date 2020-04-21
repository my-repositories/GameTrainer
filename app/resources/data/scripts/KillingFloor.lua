local keyCodes = require('scripts/shared/key-codes')
local api = require('scripts/shared/api')

processName = 'KillingFloor.exe'
entries = readFile('KillingFloor.CT')

registeredKeys = {
    keyCodes.VK_F6,
    keyCodes.VK_F7,
    keyCodes.VK_F8,
    keyCodes.VK_F9,
    keyCodes.VK_F11
}

godmode = false
noreload = false

function toggleCheat(cheat, name)
    if cheat then
        print(name .. ' enabled')
        api.playWAV('sounds/on.wav')
    else
        print(name .. ' disabled')
        api.playWAV('sounds/off.wav')
    end
end

function handleKey (key, shift, ctrl, alt)
    if key == keyCodes.VK_F6 then
        godmode = not godmode
        toggleCheat(godmode, 'godmode')
    elseif key == keyCodes.VK_F7 then
        noreload = not noreload
        toggleCheat(noreload, 'noreload')
    elseif key == keyCodes.VK_F8 then
        api.addValueTo(entries.money, 1000)
        print('increase money')
        api.playWAV('sounds/money.wav')
    elseif key == keyCodes.VK_F9 and shift and ctrl and alt then
        print('level up for all perks')
        api.playMP3('sounds/surprise.mp3')
    elseif key == keyCodes.VK_F11 then
        api.stopMP3('')
    end
end

function tick()
    if godmode then
    -- addValueTo(entries.health, 100)
    -- addValueTo(entries.armor, 100)
    end

    if noreload then
        -- addValueTo(entries.ammo_magazine, 30)
        -- addValueTo(entries.ammo_total, 30)
        -- addValueTo(entries.ammo_gren, 5)
    end
end

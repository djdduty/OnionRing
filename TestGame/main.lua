print("Hello from Lua Global!")

frameCount = 0
frameTimer = 0

function onion.load()
    print("Hello from onion load!");
end

function onion.draw()
    --print("draw!")
end

function onion.update(deltatime)
    frameTimer = frameTimer + deltatime
    frameCount = frameCount + 1
    -- print ("update... " .. frameTimer)

    if frameTimer >= 1000 then
        print ("Fps: " .. frameCount)
        frameCount = 0
        frameTimer = 0
    end
end

function onion.unload()
    print("Done")
end

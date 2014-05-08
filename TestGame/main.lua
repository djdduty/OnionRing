print("Hello from Lua!")
require("test")

total_time = 0
frame_count = 0

function onion.load()
    print("Hello from onion load!");
end

function onion.draw()
    print("draw!");
end

function onion.update(deltatime)
    total_time = total_time + deltatime
    frame_count = frame_count + 1
    print "update!"

    if frame_count >= 10 then
        onion.quit()
    end
end

function onion.unload()
    print("Done");
    print ("Total time:  " .. total_time .. " ms")
    print ("Frame count: " .. frame_count)
end

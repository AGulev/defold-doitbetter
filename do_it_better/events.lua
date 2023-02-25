local M = {}

local random = nil
local function uuid()
    if not random then
        random = math.random
        math.randomseed(100000 * (socket.gettime() % 1))
    end
    local template ='xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'
     local result = string.gsub(template, '[xy]', function (c)
        local v = (c == 'x') and random(0, 0xf) or random(8, 0xb)
        return string.format('%x', v)
    end)
    return result
end

local EVENT_KEY_AMOUNT = "amnt"
local EVENT_KEY_CURRENCY = "cur"
local EVENT_KEY_SOURCE = "src"
local EVENT_KEY_INFO= "info"

local EVENT_NAME_PURCHASE = "iap"
local EVENT_NAME_REVENUE = "revenue"
local EVENT_NAME_LOCAL_PURCHASE = "local_pur"
function M.track_purchase(amount, currency_code, transaction_id)
    do_it_better.send_event(EVENT_NAME_PURCHASE, {
        [EVENT_KEY_AMOUNT] = amount,
        [EVENT_KEY_CURRENCY] = currency_code
    }, transaction_id or uuid())
end

function M.track_local_purchase(amount, currency_code, source, info)
    do_it_better.send_event(EVENT_NAME_LOCAL_PURCHASE, {
        [EVENT_KEY_AMOUNT] = amount,
        [EVENT_KEY_CURRENCY] = currency_code,
        [EVENT_KEY_SOURCE] = source,
        [EVENT_KEY_INFO] = info,
    }, uuid())
end

function M.track_revenue(amount, currency_code, source)
    do_it_better.send_event(EVENT_NAME_REVENUE, {
        [EVENT_KEY_AMOUNT] = amount,
        [EVENT_KEY_CURRENCY] = currency_code,
        [EVENT_KEY_SOURCE] = source
    }, uuid())
end

return M

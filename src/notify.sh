#!/bin/bash
URL="https://api.telegram.org/bot6640230777:AAEvtSKGTXqYHiF6jPYcY7bdyq8PySPbWfY/sendMessage"
TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AStatus:+$CI_JOB_STATUS%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s -d "chat_id=1790035889&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
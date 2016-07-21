/**
* Copyright 2016 IBM Corp. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#ifndef WDC_CONVERSATION_MODELS_H
#define WDC_CONVERSATION_MODELS_H

#include "utils/ISerializable.h"


struct ConversationIntent : public ISerializable
{
    std::string m_Intent;
    float m_fConfidence;

    virtual void Serialize(Json::Value & json)
    {
        json["confidence"] = m_fConfidence;
        json["intent"] = m_Intent;
    }

    virtual void Deserialize(const Json::Value & json)
    {
        if ( json.isMember("confidence") )
            m_fConfidence = json["confidence"].asFloat();
        if ( json.isMember("intent") )
            m_Intent = json["intent"].asString();
    }
};


struct ConversationMessageResponse : public ISerializable
{
    RTTI_DECL();

    std::string m_ConversationId;
    std::vector<ConversationIntent> m_Intents;
    std::vector<std::string> m_Output;

    virtual void Serialize(Json::Value & json)
    {
        json["context"]["conversation_id"] = m_ConversationId;
        SerializeVector("intents", m_Intents, json);
        SerializeVector("text", m_Output, json["output"]);
    }

    virtual void Deserialize(const Json::Value & json)
    {
        if( json.isMember("intents"))
            DeserializeVector("intents", json, m_Intents);

        if( json.isMember("output") && json["output"].isMember("text") )
            DeserializeVector("text", json["output"], m_Output);

        if( json.isMember("context") && json["context"].isMember("conversation_id"))
            m_ConversationId = json["context"]["conversation_id"].asString();

    }
};

#endif

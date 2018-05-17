//BuffInstance* BuffInstance::GetBuffPtr()
//{
//	auto ptr = (LSLObject*)*(DWORD*)(MAKEPTR(oLocalPlayer));
//	if (ptr != nullptr)
//	{
//
//		auto buffBegin = *ptr->GetBegin();
//		auto buffEnd = *ptr->GetEnd();
//
//		if (buffBegin != nullptr && buffEnd != nullptr)
//		{
//			for (uint32_t i = 0; i < (buffEnd - buffBegin) / sizeof(BuffInstance); i++)
//			{
//				auto buffNode = buffBegin + i;
//				auto buffInst = buffNode->buffInst;
//
//				if (buffNode != nullptr && buffInst != nullptr)
//				{
//					if (buffInst->IsValid())
//					{
//						auto base = buffInst->GetScriptBaseBuff();
//						if (base)
//						{
//							//bufflist.push_back(buffInst);
//							ENGINE_MSG("i(%02x) : (%.f : %.f) : (%s)\n", *buffInst->GetIndex(), *buffInst->GetStartTime(), *buffInst->GetEndTime(), base->GetName());
//						}
//					}
//
//				}
//			}
//		}
//
//	}
//	return nullptr;
//}

//std::vector<BuffInstance*> ObjectManager::GetBuffList(DWORD object)
//{
//	std::vector<BuffInstance*>bufflist;
//	auto ptr = (LSLObject*)object;//(LSLObject*)*(DWORD*)(MAKEPTR(oLocalPlayer));
//	if (ptr != nullptr)
//	{
//		
//			auto buffBegin = *ptr->GetBegin();
//			auto buffEnd = *ptr->GetEnd();
//
//			if (buffBegin != nullptr && buffEnd != nullptr)
//			{
//				for (uint32_t i = 0; i < (buffEnd - buffBegin) / sizeof(BuffInstance); i++)
//				{
//					auto buffNode = buffBegin + i;
//					auto buffInst = buffNode->buffInst;
//
//					if (buffNode != nullptr && buffInst != nullptr)
//					{
//						if (buffInst->IsValid())
//						{
//							auto base = buffInst->GetScriptBaseBuff();
//							if (base)
//							{
//
//							bufflist.push_back(buffInst);
//							
//							}
//						}
//						
//						//return buffInst;
//					}
//				}
//			}
//		
//	}
//	return bufflist;
//}
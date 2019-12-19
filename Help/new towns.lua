-- Credits: Heromant, sergroj
local function f_TownTypes(define)
    SetCount(9)
    
    Array{0x6436A4, CountBefore = 1}.i4  'NativeLand'
    Ref{0x43D4F5, 0x44C2B1, 0x5C1847}

    Array{0x6408D8}.i4  'NativeLandRMG'
    Ref{0x532FA1}
    
    Array{0x6436CC} pc  'MP3'
    Ref{0x5C70F5}
    
    Array{0x6A755C} pc  'Name'
    Ref{0x40C9AB, 0x5697FA, 0x57635D, 0x58D95D, 0x58DD27, 0x5C1857}
    
    Array{0x68277C} pc  'NameLowerCase'
    Ref{0x54A4AC}

    Array{0x6A60B0}.array(16) pc  'TownNames'
    Ref{0x4CA9D3}
    
    Array{0x6971F0}.array(0x18).u1  'internal_TownNamesIndex'
    Ref{0x4CA757, 0x4CA990, 0x4CA9B2}
    EndRef{0x4CA78B}
    function RelocInfo.new(p)
        mem.call(0x4CA6D0, 1, p)
    end
    function RelocInfo.free(p)
        mem.call(0x4CA700, 1, p)
    end
    
    -- puzzle
    
    Array{0x6818D0} pc  'PuzzleNamePart'
    Ref{0x52C9CD, 0x52CF5C}
    
    Array{0x6818F4}.array(2).array(48).i2  'PuzzlePieces'
    Ref{0x52CC05, 0x52CC0C, 0x52CF97, 0x52CF9E}
    
    Array{0x681FB4}.array(48).i2  'PuzzlePiecesOrder'
    Ref{0x52CBF6, 0x52CF6C}
    
    -- on map

    Array{0x677A0C} pc  'MapTownDef'
    Ref{0x4C9823}

    Array{0x677A30} pc  'MapCastleDef'
    Ref{0x4C9810}

    Array{0x677A54} pc  'MapCapitolDef'
    Ref{0x4C97C4}

    -- monsters
    
    Array{0x6747B4}.array(14).i4  'Monsters'
    Ref{0x428605, 0x428967, 0x429BB4, 0x429DEF, 0x429F35, 0x42A029, 0x42B53B, 0x42B5DC, 0x42B5F6, 0x42B727, 0x42BE45, 0x42CF0A, 0x42D244, 0x432E97, 0x432F62, 0x43363E, 0x47AA82, 0x47AA93, 0x47AB03, 0x47AB14, 0x47AB83, 0x47AB94, 0x4BF30A, 0x4C8D30, 0x503293, 0x51CFDB, 0x525AB0, 0x52A31E, 0x5519AA, 0x551B6B, 0x576457, 0x5BE386, 0x5BE3AE, 0x5BEFA1, 0x5BFC69, 0x5BFFE2, 0x5C009B, 0x5C0206, 0x5C0267, 0x5C0582, 0x5C0B37, 0x5C0BEF, 0x5C6026, 0x5C7199, 0x5C7CE8, 0x5C7D21, 0x5D9DE7, 0x5D9E60, 0x5D9ED6, 0x5D9F4F, 0x5D9FC8, 0x5DA041, 0x5DA0C5, 0x5DA1BD, 0x5DD09C, 0x5DD96E, 0x5DDAD9}
    Ref{0x47AB36, 0x4BF304, 0x525A8E, 0x5765AC, 0x5C052B}
    Ref{0x42BCCC, 0x47ABB8, 0x4C69B2, 0x5218F7, 0x521910, 0x521954, 0x5219B5, 0x551A17, 0x5C803A}

    Array{0x68295C, CountBefore = 1} pc  'MonstersBackground'
    Ref{0x449650, 0x550012, 0x551E38, 0x5F5453}
    
    Array{0x68A344, CountBefore = 1} pc  'MonstersBackgroundInCastle'
    Ref{0x5D90A7, 0x5D9359}

    Array{0x642EA0}.i4  'BlacksmithMonster'
    Ref{0x5D17B2, 0x5D18C4, 0x5D1B05, 0x5D1FA4, 0x5D1FD6, 0x5D224F, 0x5D228C}
    
    Array{0x6AAA60}.array(2).i4  'BlacksmithArtifact'
    Ref{0x525DE3, 0x5D1D8C, 0x5D1EC1, 0x5D1ECE, 0x5D2242}
    
    -- picture screen
    
    Array{0x643050} pc  'BackgroundPrefix'
    Ref{0x5C6E43}
    
    Array{0x642EC4}.array(44).i4  'BuildingsDrawOrder'
    Ref{0x5C6EB4, 0x5C6FE8}

    Array{0x643074}.array(44) pc  'BuildingsDefs'
    Ref{0x5C6EEC}
    
    Array{0x68A3DC}.array(44) pc  'BuildingsSelection'  -- the same names are also used for TZ* contours
    Ref{0x5C3396}
    
    -- town hall
    
    Array{0x68A36C} pc  'MageGuildWindow'
    Ref{0x5CCEDA}
    
    Array{0x67F5D4} pc  'HallBuildingsDef'
    Ref{0x5D5B21, 0x5D9A6D}

    Array{0x65F4C4, CountBefore = (0x65F53C-0x65F4C4)/4} pc  'HallBuildingsDef2'
    Ref{0x407126, 0x40716A, 0x407193}
    Alias 'HallBuildingsDef'
    
    Array{0x6755B8}.array(44) pc  'HallBildingsIcons'
    Ref{0x484162}
    
    -- Array{0x66CF98}.array(18).i4  'HallBuildingsNumbers'  -- overwritten by hook at 0x461049 instead
    -- Ref{0x460DE5}
    
    Array{0x66D03C}.i4  'HallBuildingSlotsCount'  -- generated from Buildings
    Ref{0x460DD3, 0x46103A, 0x46131F, 0x4613B0, 0x4613CE, 0x461411, 0x46142D, 0x4614C4, 0x4614E0, 0x46162F}

    -- buildings data
    
    Array{0x6887F0}.array(2).struct(HordeBuildingData)  'HordeBuildings'
    Ref{0x5BE36A, 0x5BEDA7, 0x5BFB2E, 0x5BFBE4, 0x5BFBEF, 0x5C015F, 0x5C0186, 0x5C166E}
    
    Array{0x68A3B4}.array(2).u1  'Horde1MonLevel'
    Ref{0x5C7CD5, 0x5D38F6, 0x5D3931}

    Array{0x68A3C8}.array(2).u1  'Horde2MonLevel'
    Ref{0x5C7D0E, 0x5D4205, 0x5D423E}

    Array{0x688F04}.struct(ResourcesData)  'ResourceSilo'
    Ref{0x5BFA94, 0x5C1690}
    
    Array{0x688910}.struct(TownSetupMapping)  'SetupMapping'
    Ref{0x484327, 0x5C0323, 0x5C0E23, 0x5C0EFD}
    
    -- also used: Buildings, BuildingDecorations
    
    -- dependancies
    
    Array{0x6977E8}.array(44).u8  'BuildingsDependMasks'  -- generated from Buildings
    Ref{0x42B284, 0x42B293, 0x5C11DA, 0x5C11E1, 0x5C12E8, 0x5C12EF, 0x5C137A, 0x5C1381, 0x5D6018, 0x5D601F}
    Ref{0x4EB852, 0x4EB885, 0x4EB88E, 0x4EB8F5, 0x4EB8FC, 0x4EB917, 0x4EB91E, 0x4EB92A, 0x4EB931, 0x4EB938, 0x4EB93F, 0x4EB948, 0x4EB94F, 0x4EB958, 0x4EB9B3, 0x4EB9BA, 0x4EB9D5, 0x4EB9DC, 0x4EB9E8, 0x4EB9EF, 0x4EB9F6, 0x4EB9FD, 0x4EBA06, 0x4EBA0D, 0x4EBA16, 0x4EBA34, 0x4EBA43, 0x4EBA57, 0x4EBA6B, 0x4EBA7F, 0x4EBA93}
    
    Array{0x697740}.u8  'BuildingsMask'  -- generated from Buildings
    Ref{0x5C035C, 0x5C0363, 0x5C0D75, 0x5C0D84, 0x5C0E9F, 0x5C0EA6, 0x5C0FEB, 0x5C0FF4, 0x5C3839, 0x5C3842, 0x5D374C, 0x5D3756, 0x5D378D, 0x5D3796}
    Ref{0x4EB81C, 0x4EB822, 0x4EB82A, 0x4EB845, 0x4EB84B, 0x4EB85C, 0x4EB8B9, 0x4EB8BF, 0x4EB8C7, 0x4EB8E0, 0x4EB8E6, 0x4EB8EE, 0x4EB977, 0x4EB97D, 0x4EB985, 0x4EB99E, 0x4EB9A4, 0x4EB9AC, 0x4EBA2F, 0x4EBA4D, 0x4EBA61, 0x4EBA75, 0x4EBA89, 0x4EBA9D}
    
    Array{0x6A8C20}.array(44).u8  'BuildingsReplaceMasks'  -- generated from Buildings
    Ref{0x5BED82, 0x5BED8B, 0x5BF2E6, 0x5BF2ED, 0x5BF785, 0x5BF78C, 0x5C03A7, 0x5C03AE, 0x5C0C67, 0x5C0C6E, 0x5C0D11, 0x5C0D18, 0x5C0F0A, 0x5C0F1B,  0x5D606D}
    Ref{0x4EBAAC, 0x4EBAB1, 0x4EBAB7, 0x4EBABD, 0x4EBAC2, 0x4EBAD3, 0x4EBAE7, 0x4EBAEC, 0x4EBAF2, 0x4EBAF8, 0x4EBAFD, 0x4EBB0E, 0x4EBB22, 0x4EBB27, 0x4EBB2D, 0x4EBB33, 0x4EBB38, 0x4EBB49, 0x4EBB5D, 0x4EBB62, 0x4EBB68, 0x4EBB6E, 0x4EBB73, 0x4EBB84, 0x4EBB93, 0x4EBBA2, 0x4EBBB1, 0x4EBBC0, 0x4EBBCF}
    
    -- Resources
    
    Array{0x6A8344}.array(17, 25).struct(ResourcesData)  'BuildingsCost'
    Ref{0x5BF829, 0x5C14BB, 0x5C153C, 0x5C15BE}

    Array{0x6A9880}.array(30, 43).struct(ResourcesData)  'DwellingsCost'
    Ref{0x5BF848, 0x5C14DC, 0x5C1569, 0x5C15DD}
    Alias 'BuildingsCost'

    -- buildings texts
    
    Array{0x6A543C}.struct(SpecialBuildingsNames)  'BuildingsNames'
    Ref{0x460CD3, 0x460CF0, 0x46146C, 0x46148B, 0x4617F3, 0x461824, 0x461960, 0x461991, 0x4619E8, 0x461A07, 0x461A54, 0x461A7F}
    Ref{0x5C7D42, 0x5EA141, 0x5EA2C2}
    Ref{0x460CD3, 0x46146C, 0x4617F3, 0x461960, 0x4619E8, 0x461A54, 0x5EA2C2}

    Array{0x6A7874}.struct(SpecialBuildingsNames)  'BuildingsDescriptions'
    Ref{0x5D2EB1, 0x5D2F28}
    
    Array{0x6A6310}.array(30, 43) pc  'DwellingsNames'
    Ref{0x460D04, 0x4614A0, 0x461842, 0x4619AF, 0x461A1C, 0x461A9A}
    Alias 'BuildingsNames'
    
    Array{0x6A6A2C}.array(30, 43) pc  'DwellingsDescriptions'
    Ref{0x5D3143}
    Alias 'BuildingsDescriptions'
    
    Array{0x6A7ED8}.array(16, 16) pc  'BuildingsDescriptionsBlacksmith'
    Ref{0x5D2E67}
    Alias 'BuildingsDescriptions'
    
    -- combat
    
    Array{0x63BD18}.i4  'MoatDamage'
    Ref{0x421760, 0x4217C3, 0x465FDF, 0x469A88, 0x4B31D0, 0x4B3204}

    -- also used: SiegePicturesPrefix
    
    Array{0x63D2A0} pc  'SiegeBackground'  -- generated from SiegePicturesPrefix
    Ref{0x4642CB}

    Array{0x66D848}.array(18).struct(WallSection)  'SiegeWalls'  -- generated from SiegePicturesPrefix
    Ref{0x462FBA, 0x465EE9, 0x479C39, 0x479C86, 0x4929F3, 0x493923, 0x493967, 0x494259, 0x494260, 0x49437C, 0x494384, 0x4945C9, 0x4945D1, 0x4947C3, 0x4955C2}
    --[[ Differences in towns:
    (Rampart)
    66d8e0 66db68  SgCsTpWl.pcx SgRmTpW1.pcx
    66d898 66dda8  SgCsMoat.pcx
    66d8bc 66ddcc  SgCsMlip.pcx
    (Conflux)
    66d8e0 66e300  SgCsTpWl.pcx SgNcTpW1.pcx
    66d8e0 66e588  SgCsTpWl.pcx SgDnTpW1.pcx
    66d8e0 66e810  SgCsTpWl.pcx SgStTpW1.pcx
    66d910 66ed50  SgCsTw21.pcx SgElTw22.pcx
    66d914 66ed54  SgCsTw21.pcx
    66d938 66ed78  SgCsWa61.pcx
    66d980 66edc0  SgCsWa41.pcx
    66d9a4 66ede4  SgCsArch.pcx
    66d9c8 66ee08  SgCsWa31.pcx
    66da10 66ee50  SgCsWa11.pcx
    66da34 66ee74  SgCsTw11.pcx
    66da58 66ee98  SgCsMan1.pcx
    (others match Castle)
    ]]
    
    Array{0x63CF88}.struct(TownTowers)  'SiegeTowers'
    Ref{0x466868}
    
    Array{0x63BD40}.array(2).struct(CombatHeroDef)  'CombatHeroDef'  -- Male, Female
    Ref{0x463079, 0x5A040F, 0x5A04BF, 0x5A04CB, 0x5A051D, 0x5A057F, 0x5A241E}
end
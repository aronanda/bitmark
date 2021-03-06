// Copyright (c) 2010 Satoshi Nakamoto
// Original Code: Copyright (c) 2009-2014 The Bitcoin Core Developers
// Modified Code: Copyright (c) 2014, 2015, 2016 - Project Bitmark
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

// Hard-Coded (Fixed) Network Nodes
// Verified on January 6, 2016
unsigned int pnSeed[] =
{
//	0xac1f1f0a, 		// *** inoperative ***
	0xAE240982,		// Bitmark.co 
//	0x253b1359,		// *** inoperative *** 
	0x2D2141A1,		// us.bitmark.io
	0x8BA2805C,		// eu.bitmark.io
	0xCC447A0B		// one.zmark.org
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xf9;
        pchMessageStart[1] = 0xbe;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xd9;
        vAlertPubKey = ParseHex("04bf5a75ff0f823840ef512b08add20bb4275ff6e097f2830ad28645e28cb5ea4dc2cfd0972b94019ad46f331b45ef4ba679f2e6c87fd19c864365fadb4f8d2269");
        nDefaultPort = 9265;
        nRPCPort = 9266;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 32);
        nSubsidyHalvingInterval = 788000;

        // Build the genesis block.
        const char* pszTimestamp = "13/July/2014, with memory of the past, we look to the future. TDR";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 20 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04f88a76429dad346a10ecb5d36fcbf50bc2e009870e20c1a6df8db743e0b994afc1f91e079be8acc380b0ee7765519906e3d781519e9db48259f64160104939d8") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1405274442;
        genesis.nBits    = 0x1d00ffff;
        genesis.nNonce   = 14385103;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0xc1fb746e87e89ae75bdec2ef0639a1f6786744639ce3d0ece1dcf979b79137cb"));
        assert(genesis.hashMerkleRoot == uint256("0xd4715adf41222fae3d4bf41af30c675bc27228233d0f3cfd4ae0ae1d3e760ba8"));

        // todo add more dns seeders
        vSeeds.push_back(CDNSSeedData("bitmark.co", "seed.bitmark.co"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(85); // b
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(213);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.

    	// Testnet Genesis has a lower difficulty
        pchMessageStart[0] = 0x0b;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0x09;
        pchMessageStart[3] = 0x07;
        vAlertPubKey = ParseHex("0468770c9d451dd5d6d373ae6096d4ab0705c4ab66e55cc25c40788580039bd04b7672322b9bd26ce22a3ad95f490d7d188a905ce30246b2425eca8cc5102190d0");
        nDefaultPort = 19265;
        nRPCPort = 19266;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        strDataDir = "testnet3";

        genesis.nTime = 1405274408;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 16687;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x1d6329aeff3ff6786635afd5d6715b24667329cfda199bd7a1d6626d81a4573c"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("bitmark.co", "test.bitmark.co"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(130); // u
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(258);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1405274400;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}

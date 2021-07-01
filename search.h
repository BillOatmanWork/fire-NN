/*
  Fire is a freeware UCI chess playing engine authored by Norman Schmidt.

  Fire utilizes many state-of-the-art chess programming ideas and techniques
  which have been documented in detail at https://www.chessprogramming.org/
  and demonstrated via the very strong open-source chess engine Stockfish...
  https://github.com/official-stockfish/Stockfish.
  
  Fire is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or any later version.

  You should have received a copy of the GNU General Public License with
  this program: copying.txt.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <atomic>

#include "chrono.h"
#include "fire.h"
#include "position.h"

typedef movelist<max_pv> principal_variation;

struct search_signals
{
	std::atomic_bool stop_analyzing, stop_if_ponder_hit;
};

namespace search
{
	inline search_signals signals;
	inline search_param param;
	inline bool running;

	void init();
	void reset();
	void adjust_time_after_ponder_hit();
	extern uint8_t lm_reductions[2][2][64 * static_cast<int>(plies)][64];

	enum nodetype
	{
		PV, nonPV
	};

	inline int counter_move_bonus[max_ply];

	inline int counter_move_value(const int d)
	{
		return counter_move_bonus[static_cast<uint32_t>(d) / plies];
	}

	inline int history_bonus(const int d)
	{
		return counter_move_bonus[static_cast<uint32_t>(d) / plies];
	}

	struct easy_move_manager
	{
		void clear()
		{
			key_after_two_moves = 0;
			third_move_stable = 0;
			pv[0] = pv[1] = pv[2] = no_move;
		}

		[[nodiscard]] uint32_t expected_move(const uint64_t key) const
		{
			return key_after_two_moves == key ? pv[2] : no_move;
		}
		
		void refresh_pv(position& pos, const principal_variation& pv_new)
		{
			assert(pv_new.size() >= 3);

			third_move_stable = pv_new[2] == pv[2] ? third_move_stable + 1 : 0;

			if (pv_new[0] != pv[0] || pv_new[1] != pv[1] || pv_new[2] != pv[2])
			{
				pv[0] = pv_new[0];
				pv[1] = pv_new[1];
				pv[2] = pv_new[2];

				pos.play_move(pv_new[0]);
				pos.play_move(pv_new[1]);
				key_after_two_moves = pos.key();
				pos.take_move_back(pv_new[1]);
				pos.take_move_back(pv_new[0]);
			}
		}

		int third_move_stable;
		uint64_t key_after_two_moves;
		uint32_t pv[3];
	};

	inline easy_move_manager easy_move;
	inline int draw[num_sides];
	inline uint64_t previous_info_time;

	template <nodetype nt>
	int alpha_beta(position& pos, int alpha, int beta, int depth, bool cut_node);

	template <nodetype nt, bool state_check>
	int q_search(position& pos, int alpha, int beta, int depth);

	int value_to_hash(int val, int ply);
	int value_from_hash(int val, int ply);
	void copy_pv(uint32_t* pv, uint32_t move, uint32_t* pv_lower);
	void update_stats(const position& pos, bool state_check, uint32_t move, int depth, uint32_t* quiet_moves, int quiet_number);
	void update_stats_quiet(const position& pos, bool state_check, int depth, uint32_t* quiet_moves, int quiet_number);
	void update_stats_minus(const position& pos, bool state_check, uint32_t move, int depth);
	void send_time_info();
	
	inline uint8_t lm_reductions[2][2][64 * static_cast<int>(plies)][64];
	
	// alphabeta
	inline int max_gain_value = 500;

	inline int razor_margin = 384;
	inline int razoring_min_depth = 4;
	inline int razoring_qs_min_depth = 2;
	
	inline int futility_min_depth = 7;
	inline auto futility_value_0 = 0;
	inline auto futility_value_1 = 112;
	inline auto futility_value_2 = 243;
	inline auto futility_value_3 = 376;
	inline auto futility_value_4 = 510;
	inline auto futility_value_5 = 646;
	inline auto futility_value_6 = 784;
	inline auto futility_margin_ext_mult = 160;
	inline auto futility_margin_ext_base = 204;

	inline int null_move_min_depth = 2;
	inline int null_move_tempo_mult = 2;
	inline int null_move_strong_threat_mult = 8;
	inline int null_move_pos_val_less_than_beta_mult = 12;
	inline int null_move_max_depth = 8;

	inline int null_move_tm_base = 540;
	inline int null_move_tm_mult = 66;

	inline int null_move_depth_greater_than_mult = 310;
	inline int null_move_depth_greater_than_div = 204;
	inline int null_move_depth_greater_than_sub = 20;
	inline int null_move_depth_greater_than_cut_node_mult = 15;

	inline int value_less_than_beta_margin = 100;
	inline int value_greater_than_beta_max_depth = 12;
	inline int dummy_null_move_threat_min_depth_mult = 6;

	inline int no_early_pruning_min_depth = 5;
	inline int no_early_pruning_strong_threat_min_depth = 8;
	inline int pc_beta_margin = 160;
	inline int pc_beta_depth_margin = 4;
	inline int limit_depth_min = 8;
	inline int no_early_pruning_pv_node_depth_min = 5;
	inline int no_early_pruning_non_pv_node_depth_min = 8;
	inline int no_early_pruning_position_value_margin = 102;

	inline int only_quiet_check_moves_max_depth = 8;
	inline int excluded_move_min_depth = 8;
	inline int excluded_move_hash_depth_reduction = 3;
	inline int excluded_move_r_beta_hash_value_margin_mult = 8;
	inline int excluded_move_r_beta_hash_value_margin_div = 5;

	inline int late_move_count_max_depth = 16;

	inline int quiet_moves_max_depth = 6;
	inline int quiet_moves_max_gain_base = -44;
	inline int quiet_moves_max_gain_mult = 12;
	inline int sort_cmp_sort_value = -200;

	inline int predicted_depth_max_depth = 7;
	inline int predicted_depth_see_test_base = 300;
	inline int predicted_depth_see_test_mult = 20;

	inline int non_root_node_max_depth = 7;
	inline int non_root_node_see_test_base = 150;
	inline int non_root_node_see_test_mult = 20;

	inline int lmr_min_depth = 3;
	inline int stats_value_sort_value_add = 2000;
	inline int r_stats_value_div = 2048;
	inline int r_stats_value_mult_div = 8;
	inline int lmr_reduction_min = 5;

	inline int fail_low_counter_move_bonus_min_depth_mult = 3;
	inline int fail_low_counter_move_bonus_min_depth_margin = 30;
	inline int fail_low_counter_move_bonus_min_depth = 3;
	inline int counter_move_bonus_min_depth = 18;

	const int futility_values[7] =
	{
		futility_value_0, futility_value_1, futility_value_2,
		futility_value_3, futility_value_4, futility_value_5,
		futility_value_6
	};

	inline int futility_margin(const int d)
	{
		return futility_values[static_cast<uint32_t>(d) / plies];
	}

	inline int futility_margin_ext(const int d)
	{
		return futility_margin_ext_base + futility_margin_ext_mult * static_cast<int>(static_cast<uint32_t>(d) / plies);
	}

	constexpr int late_move_number_values[2][32] =
	{
		{0, 0, 3, 3, 4, 5, 6, 7, 8, 10, 12, 15, 17, 20, 23, 26, 30, 33, 37, 40, 44, 49, 53, 58, 63, 68, 73, 78, 83, 88, 94, 100},
		{0, 0, 5, 5, 6, 7, 9, 11, 14, 17, 20, 23, 27, 31, 35, 40, 45, 50, 55, 60, 65, 71, 77, 84, 91, 98, 105, 112, 119, 127, 135, 143}
	};

	inline int late_move_number(const int d, const bool progress)
	{
		return late_move_number_values[progress][static_cast<uint32_t>(d) / (plies / 2)];
	}

	inline int lmr_reduction(const bool pv, const bool vg, const int d, const int n)
	{
		return lm_reductions[pv][vg][std::min(d, 64 * static_cast<int>(plies) - 1)][std::min(n, 63)];
	}

	// qsearch
	inline int qs_futility_value_0 = 102;
	inline int qs_futility_value_1 = 0;
	inline int qs_futility_value_2 = 308;
	inline int qs_futility_value_3 = 818;
	inline int qs_futility_value_4 = 827;
	inline int qs_futility_value_5 = 1186;
	inline int qs_futility_value_6 = 2228;
	inline int qs_futility_value_7 = 0;

	const int q_search_futility_value[num_pieces] =
	{
		qs_futility_value_0, qs_futility_value_1, qs_futility_value_2, qs_futility_value_3,
		qs_futility_value_4, qs_futility_value_5, qs_futility_value_6, qs_futility_value_7,
		qs_futility_value_0, qs_futility_value_1, qs_futility_value_2, qs_futility_value_3,
		qs_futility_value_4, qs_futility_value_4, qs_futility_value_6, qs_futility_value_7
	};

	inline int lazy_margin = 480; // sf uses 1400 (* 100 / 256 = 547), but 480 seems optimal here
	inline int qs_futility_basis_margin = 102;
	inline int qs_futility_value_capture_history_add_div = 32;
	inline int qs_stats_value_sortvalue = -12000;
	inline int qs_skip_see_test_value_greater_than_alpha_sort_value = 1000;
	inline int qs_skip_see_test_value_less_than_equal_to_alpha_sort_value = 2000;
}

// mainthread::begin_search
inline int default_draw_value = 24;

// thread::begin_search
inline int v_singular_margin = 102;
inline int delta_alpha_margin = 14;
inline int delta_beta_margin = 14;
inline int value_pawn_mult = 20;

inline int improvement_factor_min_base = 1304;
inline int improvement_factor_max_base = 652;
inline int improvement_factor_max_mult = 160;
inline int improvement_factor_bv_mult = 12;

inline int best_value_vp_mult = 8;
inline int delta_alphabeta_value_add = 4;
inline int root_depth_mate_value_bv_add = 10;

inline int time_control_optimum_mult_1 = 124;
inline int time_control_optimum_mult_2 = 420;

inline int info_depth_interval = 1000;

template <int max_plus, int max_min>
struct piece_square_stats;
typedef piece_square_stats<24576, 24576> counter_move_values;

const int egtb_helpful = 0 * plies;
const int egtb_not_helpful = 10 * plies;

inline int tb_number;
inline bool tb_root_in_tb;
inline int tb_probe_depth;
inline int tb_score;

typedef int (*egtb_probe)(position& pos);
void filter_root_moves(position& pos);
std::string score_cp(int score);

struct rootmove
{
	rootmove() = default;

	explicit rootmove(const uint32_t move)
	{
		pv.move_number = 1;
		pv.moves[0] = move;
	}

	bool operator<(const rootmove& root_move) const
	{
		return root_move.score < score;
	}

	bool operator==(const uint32_t& move) const
	{
		return pv[0] == move;
	}

	bool ponder_move_from_hash(position& pos);
	void pv_from_hash(position& pos);

	int depth = depth_0;
	int score = -max_score;
	int previous_score = -max_score;
	int start_value = score_0;
	principal_variation pv;
};

struct rootmoves
{
	rootmoves() = default;

	int move_number = 0, dummy = 0;
	rootmove moves[max_moves];

	void add(const rootmove root_move)
	{
		moves[move_number++] = root_move;
	}

	rootmove& operator[](const int index)
	{
		return moves[index];
	}

	const rootmove& operator[](const int index) const
	{
		return moves[index];
	}

	void clear()
	{
		move_number = 0;
	}

	int find(const uint32_t move)
	{
		for (auto i = 0; i < move_number; i++)
			if (moves[i].pv[0] == move)
				return i;
		return -1;
	}
};

namespace egtb
{
	extern int max_pieces_wdl, max_pieces_dtz, max_pieces_dtm;
	extern egtb_probe egtb_probe_wdl;
	extern egtb_probe egtb_probe_dtz;
	extern egtb_probe egtb_probe_dtm;
	extern bool use_rule50;
	extern void syzygy_init(const std::string& path);
}
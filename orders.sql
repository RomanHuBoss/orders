--
-- PostgreSQL database dump
--

-- Dumped from database version 9.6.10
-- Dumped by pg_dump version 9.6.0

-- Started on 2019-07-26 01:01:52

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;


--
-- TOC entry 2230 (class 1262 OID 334096)
-- Name: orders; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE orders WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'Russian_Russia.1251' LC_CTYPE = 'Russian_Russia.1251';


ALTER DATABASE orders OWNER TO postgres;

\connect orders

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;


--
-- TOC entry 1 (class 3079 OID 12387)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2232 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 185 (class 1259 OID 334097)
-- Name: comments; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE comments (
    id integer NOT NULL,
    pid integer,
    id_task integer NOT NULL,
    id_worker integer NOT NULL,
    comment text NOT NULL,
    published_dt timestamp with time zone NOT NULL,
    title text NOT NULL
);


ALTER TABLE comments OWNER TO postgres;

--
-- TOC entry 2233 (class 0 OID 0)
-- Dependencies: 185
-- Name: TABLE comments; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE comments IS 'Название: Комментарии';


--
-- TOC entry 2234 (class 0 OID 0)
-- Dependencies: 185
-- Name: COLUMN comments.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.id IS 'Идентификатор комментария';


--
-- TOC entry 2235 (class 0 OID 0)
-- Dependencies: 185
-- Name: COLUMN comments.pid; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.pid IS 'Идентификатор родительского комментария';


--
-- TOC entry 2236 (class 0 OID 0)
-- Dependencies: 185
-- Name: COLUMN comments.id_task; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.id_task IS 'Идентификатор задачи';


--
-- TOC entry 2237 (class 0 OID 0)
-- Dependencies: 185
-- Name: COLUMN comments.id_worker; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.id_worker IS 'Идентификатор автора комментария';


--
-- TOC entry 2238 (class 0 OID 0)
-- Dependencies: 185
-- Name: COLUMN comments.comment; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.comment IS 'Содержимое комментария';


--
-- TOC entry 2239 (class 0 OID 0)
-- Dependencies: 185
-- Name: COLUMN comments.published_dt; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.published_dt IS 'Дата и время публикации';


--
-- TOC entry 2240 (class 0 OID 0)
-- Dependencies: 185
-- Name: COLUMN comments.title; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN comments.title IS 'Заголовок комментария';


--
-- TOC entry 186 (class 1259 OID 334103)
-- Name: comments_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE comments_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE comments_id_seq OWNER TO postgres;

--
-- TOC entry 2241 (class 0 OID 0)
-- Dependencies: 186
-- Name: comments_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE comments_id_seq OWNED BY comments.id;


--
-- TOC entry 187 (class 1259 OID 334105)
-- Name: department_workers; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE department_workers (
    id integer NOT NULL,
    fio text NOT NULL,
    login text NOT NULL,
    password text NOT NULL,
    id_position integer NOT NULL
);
ALTER TABLE ONLY department_workers ALTER COLUMN fio SET STATISTICS 0;
ALTER TABLE ONLY department_workers ALTER COLUMN login SET STATISTICS 0;
ALTER TABLE ONLY department_workers ALTER COLUMN password SET STATISTICS 0;


ALTER TABLE department_workers OWNER TO postgres;

--
-- TOC entry 2242 (class 0 OID 0)
-- Dependencies: 187
-- Name: TABLE department_workers; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE department_workers IS 'Название: Данные сотрудников отдела';


--
-- TOC entry 2243 (class 0 OID 0)
-- Dependencies: 187
-- Name: COLUMN department_workers.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.id IS 'Идентификатор сотрудника';


--
-- TOC entry 2244 (class 0 OID 0)
-- Dependencies: 187
-- Name: COLUMN department_workers.fio; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.fio IS 'Фамилия, имя, отчество';


--
-- TOC entry 2245 (class 0 OID 0)
-- Dependencies: 187
-- Name: COLUMN department_workers.login; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.login IS 'Логин';


--
-- TOC entry 2246 (class 0 OID 0)
-- Dependencies: 187
-- Name: COLUMN department_workers.password; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.password IS 'Пароль';


--
-- TOC entry 2247 (class 0 OID 0)
-- Dependencies: 187
-- Name: COLUMN department_workers.id_position; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN department_workers.id_position IS 'Идентификатор должности';


--
-- TOC entry 188 (class 1259 OID 334111)
-- Name: department_workers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE department_workers_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE department_workers_id_seq OWNER TO postgres;

--
-- TOC entry 2248 (class 0 OID 0)
-- Dependencies: 188
-- Name: department_workers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE department_workers_id_seq OWNED BY department_workers.id;


--
-- TOC entry 189 (class 1259 OID 334113)
-- Name: positions; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE positions (
    id integer NOT NULL,
    title text NOT NULL,
    description text,
    is_head boolean DEFAULT false NOT NULL
);


ALTER TABLE positions OWNER TO postgres;

--
-- TOC entry 2249 (class 0 OID 0)
-- Dependencies: 189
-- Name: COLUMN positions.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN positions.id IS 'Идентификатор должности';


--
-- TOC entry 2250 (class 0 OID 0)
-- Dependencies: 189
-- Name: COLUMN positions.title; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN positions.title IS 'Название должности';


--
-- TOC entry 2251 (class 0 OID 0)
-- Dependencies: 189
-- Name: COLUMN positions.description; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN positions.description IS 'Описание должности';


--
-- TOC entry 2252 (class 0 OID 0)
-- Dependencies: 189
-- Name: COLUMN positions.is_head; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN positions.is_head IS 'Признак начальника подразделения';


--
-- TOC entry 190 (class 1259 OID 334120)
-- Name: positions_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE positions_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE positions_id_seq OWNER TO postgres;

--
-- TOC entry 2253 (class 0 OID 0)
-- Dependencies: 190
-- Name: positions_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE positions_id_seq OWNED BY positions.id;


--
-- TOC entry 191 (class 1259 OID 334122)
-- Name: projects; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE projects (
    id integer NOT NULL,
    title text NOT NULL,
    description text,
    creation_dt timestamp(0) without time zone DEFAULT now() NOT NULL,
    start_date date,
    end_date date
);


ALTER TABLE projects OWNER TO postgres;

--
-- TOC entry 2254 (class 0 OID 0)
-- Dependencies: 191
-- Name: TABLE projects; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE projects IS 'Название: Проекты';


--
-- TOC entry 2255 (class 0 OID 0)
-- Dependencies: 191
-- Name: COLUMN projects.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN projects.id IS 'Идентификатор проекта';


--
-- TOC entry 2256 (class 0 OID 0)
-- Dependencies: 191
-- Name: COLUMN projects.title; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN projects.title IS 'Название проекта';


--
-- TOC entry 2257 (class 0 OID 0)
-- Dependencies: 191
-- Name: COLUMN projects.description; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN projects.description IS 'Описание проекта';


--
-- TOC entry 2258 (class 0 OID 0)
-- Dependencies: 191
-- Name: COLUMN projects.creation_dt; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN projects.creation_dt IS 'Дата создания';


--
-- TOC entry 2259 (class 0 OID 0)
-- Dependencies: 191
-- Name: COLUMN projects.start_date; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN projects.start_date IS 'Дата начала';


--
-- TOC entry 2260 (class 0 OID 0)
-- Dependencies: 191
-- Name: COLUMN projects.end_date; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN projects.end_date IS 'Дата окончания';


--
-- TOC entry 192 (class 1259 OID 334128)
-- Name: projects_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE projects_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE projects_id_seq OWNER TO postgres;

--
-- TOC entry 2261 (class 0 OID 0)
-- Dependencies: 192
-- Name: projects_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE projects_id_seq OWNED BY projects.id;


--
-- TOC entry 193 (class 1259 OID 334130)
-- Name: status_to_status; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE status_to_status (
    id_status_old integer NOT NULL,
    id_status_new integer NOT NULL,
    is_head_only boolean DEFAULT false NOT NULL,
    CONSTRAINT status_to_status_chk CHECK ((id_status_old <> id_status_new))
);
ALTER TABLE ONLY status_to_status ALTER COLUMN id_status_new SET STATISTICS 0;


ALTER TABLE status_to_status OWNER TO postgres;

--
-- TOC entry 2262 (class 0 OID 0)
-- Dependencies: 193
-- Name: COLUMN status_to_status.id_status_old; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN status_to_status.id_status_old IS 'Идентификатор старого статуса';


--
-- TOC entry 2263 (class 0 OID 0)
-- Dependencies: 193
-- Name: COLUMN status_to_status.id_status_new; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN status_to_status.id_status_new IS 'Идентификатор нового статуса';


--
-- TOC entry 2264 (class 0 OID 0)
-- Dependencies: 193
-- Name: COLUMN status_to_status.is_head_only; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN status_to_status.is_head_only IS 'Разрешено только для руководителя отдела';


--
-- TOC entry 2265 (class 0 OID 0)
-- Dependencies: 193
-- Name: CONSTRAINT status_to_status_chk ON status_to_status; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON CONSTRAINT status_to_status_chk ON status_to_status IS 'Статусы не должны совпадать';


--
-- TOC entry 194 (class 1259 OID 334135)
-- Name: statuses; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE statuses (
    id integer NOT NULL,
    title text NOT NULL,
    is_initial boolean DEFAULT false NOT NULL,
    is_final boolean DEFAULT false NOT NULL,
    is_working boolean DEFAULT false NOT NULL,
    is_need_rework boolean DEFAULT false NOT NULL,
    is_declined boolean DEFAULT false NOT NULL,
    is_checking boolean DEFAULT false NOT NULL
);


ALTER TABLE statuses OWNER TO postgres;

--
-- TOC entry 2266 (class 0 OID 0)
-- Dependencies: 194
-- Name: TABLE statuses; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE statuses IS 'Название: Статусы задач';


--
-- TOC entry 2267 (class 0 OID 0)
-- Dependencies: 194
-- Name: COLUMN statuses.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.id IS 'Идентификатор статуса';


--
-- TOC entry 2268 (class 0 OID 0)
-- Dependencies: 194
-- Name: COLUMN statuses.title; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.title IS 'Название статуса';


--
-- TOC entry 2269 (class 0 OID 0)
-- Dependencies: 194
-- Name: COLUMN statuses.is_initial; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_initial IS 'Признак статуса новой задачи';


--
-- TOC entry 2270 (class 0 OID 0)
-- Dependencies: 194
-- Name: COLUMN statuses.is_final; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_final IS 'Признак статуса завершенной задачи';


--
-- TOC entry 2271 (class 0 OID 0)
-- Dependencies: 194
-- Name: COLUMN statuses.is_working; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_working IS 'Признак статуса разрабатываемой задачи';


--
-- TOC entry 2272 (class 0 OID 0)
-- Dependencies: 194
-- Name: COLUMN statuses.is_need_rework; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_need_rework IS 'Признак статуса задачи, которую нужно доработать';


--
-- TOC entry 2273 (class 0 OID 0)
-- Dependencies: 194
-- Name: COLUMN statuses.is_declined; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_declined IS 'Признак статуса отмененной задачи';


--
-- TOC entry 2274 (class 0 OID 0)
-- Dependencies: 194
-- Name: COLUMN statuses.is_checking; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN statuses.is_checking IS 'Признак статуса проверяемой задачи';


--
-- TOC entry 195 (class 1259 OID 334147)
-- Name: statuses_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE statuses_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE statuses_id_seq OWNER TO postgres;

--
-- TOC entry 2275 (class 0 OID 0)
-- Dependencies: 195
-- Name: statuses_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE statuses_id_seq OWNED BY statuses.id;


--
-- TOC entry 196 (class 1259 OID 334149)
-- Name: task_statuses_history; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE task_statuses_history (
    id_task integer NOT NULL,
    id_status integer NOT NULL,
    id_worker integer NOT NULL,
    status_dt timestamp with time zone DEFAULT now() NOT NULL
);


ALTER TABLE task_statuses_history OWNER TO postgres;

--
-- TOC entry 2276 (class 0 OID 0)
-- Dependencies: 196
-- Name: TABLE task_statuses_history; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE task_statuses_history IS 'Название: История изменения статусов задачи';


--
-- TOC entry 2277 (class 0 OID 0)
-- Dependencies: 196
-- Name: COLUMN task_statuses_history.id_task; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN task_statuses_history.id_task IS 'Идентификатор задачи';


--
-- TOC entry 2278 (class 0 OID 0)
-- Dependencies: 196
-- Name: COLUMN task_statuses_history.id_status; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN task_statuses_history.id_status IS 'Идентификатор статуса';


--
-- TOC entry 2279 (class 0 OID 0)
-- Dependencies: 196
-- Name: COLUMN task_statuses_history.id_worker; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN task_statuses_history.id_worker IS 'Идентификатор установившего';


--
-- TOC entry 2280 (class 0 OID 0)
-- Dependencies: 196
-- Name: COLUMN task_statuses_history.status_dt; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN task_statuses_history.status_dt IS 'Время и дата установки статуса';


--
-- TOC entry 197 (class 1259 OID 334153)
-- Name: tasks; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE tasks (
    id integer NOT NULL,
    pid integer,
    id_project integer NOT NULL,
    id_worker integer NOT NULL,
    title text NOT NULL,
    description text NOT NULL,
    deadline_dt timestamp with time zone NOT NULL,
    published_dt timestamp with time zone DEFAULT now() NOT NULL
);


ALTER TABLE tasks OWNER TO postgres;

--
-- TOC entry 2281 (class 0 OID 0)
-- Dependencies: 197
-- Name: TABLE tasks; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON TABLE tasks IS 'Название: Задачи';


--
-- TOC entry 2282 (class 0 OID 0)
-- Dependencies: 197
-- Name: COLUMN tasks.id; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.id IS 'Идентификатор задачи';


--
-- TOC entry 2283 (class 0 OID 0)
-- Dependencies: 197
-- Name: COLUMN tasks.pid; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.pid IS 'Идентификатор родительской задачи';


--
-- TOC entry 2284 (class 0 OID 0)
-- Dependencies: 197
-- Name: COLUMN tasks.id_project; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.id_project IS 'Идентификатор проекта';


--
-- TOC entry 2285 (class 0 OID 0)
-- Dependencies: 197
-- Name: COLUMN tasks.id_worker; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.id_worker IS 'Идентификатор сотрудника';


--
-- TOC entry 2286 (class 0 OID 0)
-- Dependencies: 197
-- Name: COLUMN tasks.title; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.title IS 'Название задачи';


--
-- TOC entry 2287 (class 0 OID 0)
-- Dependencies: 197
-- Name: COLUMN tasks.description; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.description IS 'Описание задачи';


--
-- TOC entry 2288 (class 0 OID 0)
-- Dependencies: 197
-- Name: COLUMN tasks.deadline_dt; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.deadline_dt IS 'Планируемая дата окончания';


--
-- TOC entry 2289 (class 0 OID 0)
-- Dependencies: 197
-- Name: COLUMN tasks.published_dt; Type: COMMENT; Schema: public; Owner: postgres
--

COMMENT ON COLUMN tasks.published_dt IS 'Дата и время публикации задачи';


--
-- TOC entry 198 (class 1259 OID 334160)
-- Name: tasks_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE tasks_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE tasks_id_seq OWNER TO postgres;

--
-- TOC entry 2290 (class 0 OID 0)
-- Dependencies: 198
-- Name: tasks_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE tasks_id_seq OWNED BY tasks.id;


--
-- TOC entry 2045 (class 2604 OID 334162)
-- Name: comments id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments ALTER COLUMN id SET DEFAULT nextval('comments_id_seq'::regclass);


--
-- TOC entry 2046 (class 2604 OID 334163)
-- Name: department_workers id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY department_workers ALTER COLUMN id SET DEFAULT nextval('department_workers_id_seq'::regclass);


--
-- TOC entry 2048 (class 2604 OID 334164)
-- Name: positions id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY positions ALTER COLUMN id SET DEFAULT nextval('positions_id_seq'::regclass);


--
-- TOC entry 2049 (class 2604 OID 334165)
-- Name: projects id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY projects ALTER COLUMN id SET DEFAULT nextval('projects_id_seq'::regclass);


--
-- TOC entry 2059 (class 2604 OID 334166)
-- Name: statuses id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY statuses ALTER COLUMN id SET DEFAULT nextval('statuses_id_seq'::regclass);


--
-- TOC entry 2062 (class 2604 OID 334167)
-- Name: tasks id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks ALTER COLUMN id SET DEFAULT nextval('tasks_id_seq'::regclass);


--
-- TOC entry 2212 (class 0 OID 334097)
-- Dependencies: 185
-- Data for Name: comments; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY comments (id, pid, id_task, id_worker, comment, published_dt, title) FROM stdin;
\.


--
-- TOC entry 2291 (class 0 OID 0)
-- Dependencies: 186
-- Name: comments_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('comments_id_seq', 1, false);


--
-- TOC entry 2214 (class 0 OID 334105)
-- Dependencies: 187
-- Data for Name: department_workers; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY department_workers (id, fio, login, password, id_position) FROM stdin;
2	Рабинович Р.М.	admin	21232f297a57a5a743894a0e4a801fc3	1
3	Иванов И.И.	ivanov	4dfe6e220d16e7b633cfdd92bcc8050b	2
4	Петров П.П.	petrov	f396c3b74762b1fee69b10abb875139b	2
\.


--
-- TOC entry 2292 (class 0 OID 0)
-- Dependencies: 188
-- Name: department_workers_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('department_workers_id_seq', 4, true);


--
-- TOC entry 2216 (class 0 OID 334113)
-- Dependencies: 189
-- Data for Name: positions; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY positions (id, title, description, is_head) FROM stdin;
1	Начальник отдела	\N	t
2	Аналитик	\N	f
3	Программист	\N	f
\.


--
-- TOC entry 2293 (class 0 OID 0)
-- Dependencies: 190
-- Name: positions_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('positions_id_seq', 3, true);


--
-- TOC entry 2218 (class 0 OID 334122)
-- Dependencies: 191
-- Data for Name: projects; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY projects (id, title, description, creation_dt, start_date, end_date) FROM stdin;
1	Тестовый проект	Разработка тестового IT-проекта	2019-07-25 19:21:12	\N	\N
\.


--
-- TOC entry 2294 (class 0 OID 0)
-- Dependencies: 192
-- Name: projects_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('projects_id_seq', 1, true);


--
-- TOC entry 2220 (class 0 OID 334130)
-- Dependencies: 193
-- Data for Name: status_to_status; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY status_to_status (id_status_old, id_status_new, is_head_only) FROM stdin;
1	3	f
1	5	t
2	4	t
3	1	f
3	5	t
3	6	f
4	3	f
4	5	t
5	1	t
6	4	t
6	5	t
6	2	t
\.


--
-- TOC entry 2221 (class 0 OID 334135)
-- Dependencies: 194
-- Data for Name: statuses; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY statuses (id, title, is_initial, is_final, is_working, is_need_rework, is_declined, is_checking) FROM stdin;
1	Нужно сделать	t	f	f	f	f	f
2	Выполнено	f	t	f	f	f	f
3	В работе	f	f	t	f	f	f
4	Нужна доработка	f	f	f	t	f	f
5	Отменено	f	f	f	f	t	f
6	На проверке	f	f	f	f	f	t
\.


--
-- TOC entry 2295 (class 0 OID 0)
-- Dependencies: 195
-- Name: statuses_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('statuses_id_seq', 6, true);


--
-- TOC entry 2223 (class 0 OID 334149)
-- Dependencies: 196
-- Data for Name: task_statuses_history; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY task_statuses_history (id_task, id_status, id_worker, status_dt) FROM stdin;
\.


--
-- TOC entry 2224 (class 0 OID 334153)
-- Dependencies: 197
-- Data for Name: tasks; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY tasks (id, pid, id_project, id_worker, title, description, deadline_dt, published_dt) FROM stdin;
\.


--
-- TOC entry 2296 (class 0 OID 0)
-- Dependencies: 198
-- Name: tasks_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('tasks_id_seq', 1, false);


--
-- TOC entry 2064 (class 2606 OID 334169)
-- Name: comments comments_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments
    ADD CONSTRAINT comments_pkey PRIMARY KEY (id);


--
-- TOC entry 2066 (class 2606 OID 334171)
-- Name: department_workers department_workers_login_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY department_workers
    ADD CONSTRAINT department_workers_login_key UNIQUE (login);


--
-- TOC entry 2068 (class 2606 OID 334173)
-- Name: department_workers department_workers_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY department_workers
    ADD CONSTRAINT department_workers_pkey PRIMARY KEY (id);


--
-- TOC entry 2070 (class 2606 OID 334175)
-- Name: positions positions_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY positions
    ADD CONSTRAINT positions_pkey PRIMARY KEY (id);


--
-- TOC entry 2072 (class 2606 OID 334177)
-- Name: positions positions_title_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY positions
    ADD CONSTRAINT positions_title_key UNIQUE (title);


--
-- TOC entry 2074 (class 2606 OID 334179)
-- Name: projects projects_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY projects
    ADD CONSTRAINT projects_pkey PRIMARY KEY (id);


--
-- TOC entry 2076 (class 2606 OID 334181)
-- Name: status_to_status status_to_status_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY status_to_status
    ADD CONSTRAINT status_to_status_pkey PRIMARY KEY (id_status_new, id_status_old);


--
-- TOC entry 2078 (class 2606 OID 334183)
-- Name: statuses statuses_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY statuses
    ADD CONSTRAINT statuses_pkey PRIMARY KEY (id);


--
-- TOC entry 2080 (class 2606 OID 334185)
-- Name: task_statuses_history task_statuses_history_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY task_statuses_history
    ADD CONSTRAINT task_statuses_history_pkey PRIMARY KEY (id_task, id_status, status_dt, id_worker);


--
-- TOC entry 2082 (class 2606 OID 334187)
-- Name: tasks tasks_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT tasks_pkey PRIMARY KEY (id);


--
-- TOC entry 2083 (class 2606 OID 334188)
-- Name: comments comments_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments
    ADD CONSTRAINT comments_fk FOREIGN KEY (pid) REFERENCES comments(id) ON DELETE CASCADE;


--
-- TOC entry 2084 (class 2606 OID 334193)
-- Name: comments comments_fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments
    ADD CONSTRAINT comments_fk1 FOREIGN KEY (id_task) REFERENCES tasks(id) ON DELETE CASCADE;


--
-- TOC entry 2085 (class 2606 OID 334198)
-- Name: comments comments_fk2; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY comments
    ADD CONSTRAINT comments_fk2 FOREIGN KEY (id_worker) REFERENCES department_workers(id) ON DELETE CASCADE;


--
-- TOC entry 2086 (class 2606 OID 334203)
-- Name: department_workers department_workers_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY department_workers
    ADD CONSTRAINT department_workers_fk FOREIGN KEY (id_position) REFERENCES positions(id) ON DELETE CASCADE;


--
-- TOC entry 2087 (class 2606 OID 334208)
-- Name: status_to_status status_to_status_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY status_to_status
    ADD CONSTRAINT status_to_status_fk FOREIGN KEY (id_status_old) REFERENCES statuses(id) ON DELETE CASCADE;


--
-- TOC entry 2088 (class 2606 OID 334213)
-- Name: status_to_status status_to_status_fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY status_to_status
    ADD CONSTRAINT status_to_status_fk1 FOREIGN KEY (id_status_new) REFERENCES statuses(id) ON DELETE CASCADE;


--
-- TOC entry 2089 (class 2606 OID 334218)
-- Name: task_statuses_history task_statuses_history_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY task_statuses_history
    ADD CONSTRAINT task_statuses_history_fk FOREIGN KEY (id_task) REFERENCES tasks(id) ON DELETE CASCADE;


--
-- TOC entry 2090 (class 2606 OID 334223)
-- Name: task_statuses_history task_statuses_history_fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY task_statuses_history
    ADD CONSTRAINT task_statuses_history_fk1 FOREIGN KEY (id_status) REFERENCES statuses(id) ON DELETE CASCADE;


--
-- TOC entry 2091 (class 2606 OID 334228)
-- Name: task_statuses_history task_statuses_history_fk2; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY task_statuses_history
    ADD CONSTRAINT task_statuses_history_fk2 FOREIGN KEY (id_worker) REFERENCES department_workers(id) ON DELETE CASCADE;


--
-- TOC entry 2092 (class 2606 OID 334233)
-- Name: tasks tasks_fk; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT tasks_fk FOREIGN KEY (pid) REFERENCES tasks(id) ON DELETE CASCADE;


--
-- TOC entry 2093 (class 2606 OID 334238)
-- Name: tasks tasks_fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT tasks_fk1 FOREIGN KEY (id_project) REFERENCES projects(id) ON DELETE CASCADE;


--
-- TOC entry 2094 (class 2606 OID 334243)
-- Name: tasks tasks_fk2; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY tasks
    ADD CONSTRAINT tasks_fk2 FOREIGN KEY (id_worker) REFERENCES department_workers(id) ON DELETE CASCADE;


-- Completed on 2019-07-26 01:01:53

--
-- PostgreSQL database dump complete
--

